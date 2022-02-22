#define RAPIDJSON_ASSERT(x)

#include "JsonParser.hpp"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using namespace Reminder::Api::Parser;
using namespace Reminder::Core::Model;
using namespace rapidjson;
using namespace std;

std::string JsonParser::convertToApiString(Board &board) {
    Document document;
    Document::AllocatorType &allocator = document.GetAllocator();

    Value jsonBoard = getJsonValueFromModel(board, allocator);
    return jsonValueToString(jsonBoard);
}

std::string JsonParser::convertToApiString(List &list) {
    Document document(kObjectType);

    Value jsonList = getJsonValueFromModel(list, document.GetAllocator());
    return jsonValueToString(jsonList);
}

std::string JsonParser::convertToApiString(std::vector<List> &lists) {
    Document document(kArrayType);
    Document::AllocatorType &allocator = document.GetAllocator();

    for (List &list : lists) {
        Value jsonList = getJsonValueFromModel(list, allocator);
        document.PushBack(jsonList, allocator);
    }

    return jsonValueToString(document);
}

std::string JsonParser::convertToApiString(Item &item) {

    std::string result = EMPTY_JSON;
    Document document(kObjectType);

    Value jsonItem = getJsonValueFromModel(item, document.GetAllocator());
    result = jsonValueToString(jsonItem);
    return result;
}

std::string JsonParser::convertToApiString(std::vector<Item> &items) {
    Document document(kArrayType);
    Document::AllocatorType &allocator = document.GetAllocator();

    for (Item &item : items) {
        Value jsonItem = getJsonValueFromModel(item, allocator);
        document.PushBack(jsonItem, allocator);
    }

    return jsonValueToString(document);
}

std::optional<List> JsonParser::convertListToModel(int listid, std::string &request) {

    std::optional<List> resultList;
    Document document;
    document.Parse(request.c_str());

    if (true == isValidList(document)) {
        std::string value = document["value"].GetString();
        resultList = List(listid, value);
    }
    return resultList;
}

std::optional<Item> JsonParser::convertItemToModel(int itemid, std::string &request) {
    std::optional<Item> resultItem;
    Document document;
    document.Parse(request.c_str());
    if (true == isValidItem(document)) {
        std::string value = document["value"].GetString();
        std::string date = document["date"].GetString();
        bool flagged = document["flagged"].GetBool();
        resultItem = Item(itemid, value, flagged, date);
    }
    return resultItem;
}

std::string JsonParser::jsonValueToString(rapidjson::Value const &json) {
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    json.Accept(writer);

    return buffer.GetString();
}

rapidjson::Value JsonParser::getJsonValueFromModel(Item const &item, rapidjson::Document::AllocatorType &allocator) {
    Value jsonItem(kObjectType);

    jsonItem.AddMember("id", item.getid(), allocator);
    jsonItem.AddMember("value", Value(item.getvalue().c_str(), allocator), allocator);
    jsonItem.AddMember("flagged", item.getflag(), allocator);
    jsonItem.AddMember("date", Value(item.getdate().c_str(), allocator), allocator);

    return jsonItem;
}

rapidjson::Value JsonParser::getJsonValueFromModel(List const &list, rapidjson::Document::AllocatorType &allocator) {
    Value jsonList(kObjectType);

    jsonList.AddMember("id", list.getid(), allocator);
    jsonList.AddMember("value", Value(list.getvalue().c_str(), allocator), allocator);

    Value jsonItems(kArrayType);

    for (Item const &item : list.getitems()) {
        Value jsonItem = getJsonValueFromModel(item, allocator);
        jsonItems.PushBack(jsonItem, allocator);
    }

    jsonList.AddMember("items", jsonItems, allocator);

    return jsonList;
}

rapidjson::Value JsonParser::getJsonValueFromModel(Board &board, rapidjson::Document::AllocatorType &allocator) {
    Value jsonBoard(kObjectType);
    Value jsonLists(kArrayType);

    for (List &list : board.getlists()) {
        Value jsonList = getJsonValueFromModel(list, allocator);
        jsonLists.PushBack(jsonList, allocator);
    }

    jsonBoard.AddMember("title", Value(board.gettitle().c_str(), allocator), allocator);
    jsonBoard.AddMember("lists", jsonLists, allocator);

    return jsonBoard;
}

bool JsonParser::isValidList(rapidjson::Document const &document) {

    bool isValid = true;

    if (document.HasParseError()) {
        isValid = false;
    }
    if (false == document["value"].IsString()) {
        isValid = false;
    }

    return isValid;
}

bool JsonParser::isValidItem(rapidjson::Document const &document) {

    bool isValid = true;

    if (document.HasParseError()) {
        isValid = false;
    }
    if (false == document["value"].IsString()) {
        isValid = false;
    }
    if (false == document["date"].IsString()) {
        isValid = false;
    }
    if (false == document["flagged"].IsBool()) {
        isValid = false;
    }

    return isValid;
}
