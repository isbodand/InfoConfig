//
// Created by tudom on 2020-01-15.
//

#include <info/config/Config.hpp>
#include <info/config/exception.hpp>

#pragma warning(push, 0)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#pragma GCC diagnostic pop
#pragma warning(pop)

info::config::Config::Config(std::string_view filename) {
    try {
        xml::XMLPlatformUtils::Initialize();
    } catch (const xml::XMLException& e) {
        throw initialization_exception{e.getMessage()};
    } catch (...) {
        throw initialization_exception{{}};
    }

    std::unique_ptr<xml::XercesDOMParser> parser{new xml::XercesDOMParser};
    parser->setValidationScheme(xml::XercesDOMParser::Val_Always);
    parser->setDoNamespaces(true);

    std::unique_ptr<xml::ErrorHandler> err{new xml::HandlerBase};
    parser->setErrorHandler(err.get());

    try {
        parser->parse(filename.data());
    } catch (const xml::XMLException& e) {
        throw parsing_exception{e.getMessage()};
    } catch (const xml::DOMException& e) {
        throw parsing_exception{e.getMessage()};
    } catch (...) {
        throw parsing_exception{{}};
    }

    _doc = parser->adoptDocument();
}

info::config::Config::~Config() {
    _doc->release();

    xml::XMLPlatformUtils::Terminate();
}

std::optional<info::config::LocalXMLString> info::config::Config::get(const info::config::Accessor& acc) const {
    auto finder = [](auto self,
                     xml::DOMNode* doc,
                     const std::vector<std::string>& path) -> std::optional<LocalXMLString> {
      auto current = path.begin();
      auto* children = doc->getChildNodes();
      for (std::size_t i = 0; i < children->getLength(); ++i) {
          auto* spawn = children->item(i);
          if (spawn->getNodeType() != xml::DOMNode::NodeType::ELEMENT_NODE)
              continue;
          LocalXMLString name{spawn->getLocalName()};
          if (*current == static_cast<std::string>(name)) {
              if (path.size() == 1) {
                  return LocalXMLString{spawn->getTextContent()};
              }

              std::vector<std::string> choppedPath(path.size() - 1);
              std::copy(std::next(path.begin()), path.end(), choppedPath.begin());
              if (auto ret = self(self, spawn, choppedPath);
                     ret) {
                  return ret;
              }
          }
      }
      return std::nullopt;
    };

    return finder(finder, _doc, acc._path);
}
