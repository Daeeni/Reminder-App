#pragma once

#include "ParserIf.hpp"
#include "rapidjson/document.h"

namespace Reminder {
namespace Api {
namespace Parser {

class JsonParser : public ParserIf {
  private:
    static inline std::string const EMPTY_JSON = "{}";

    bool isValidList(rapidjson::Document const &document);
    bool isValidItem(rapidjson::Document const &document);

    std::string jsonValueToString(rapidjson::Value const &json);

    rapidjson::Value getJsonValueFromModel(Reminder::Core::Model::Item const &item, rapidjson::Document::AllocatorType &allocator);
    rapidjson::Value getJsonValueFromModel(Reminder::Core::Model::List const &list, rapidjson::Document::AllocatorType &allocator);
    rapidjson::Value getJsonValueFromModel(Reminder::Core::Model::Board &board, rapidjson::Document::AllocatorType &allocator);

  public:
    JsonParser(){};
    virtual ~JsonParser(){};

    virtual std::string convertToApiString(Reminder::Core::Model::Board &board);
    virtual std::string convertToApiString(Reminder::Core::Model::List &list);
    virtual std::string convertToApiString(std::vector<Reminder::Core::Model::List> &Lists);

    virtual std::string convertToApiString(Reminder::Core::Model::Item &item);
    virtual std::string convertToApiString(std::vector<Reminder::Core::Model::Item> &items);

    virtual std::optional<Reminder::Core::Model::List> convertListToModel(int listid, std::string &request);
    virtual std::optional<Reminder::Core::Model::Item> convertItemToModel(int itemid, std::string &request);

    virtual std::string getEmptyResponseString() {
        return JsonParser::EMPTY_JSON;
    }
};
} // namespace Parser
} // namespace Api
} // namespace Reminder
