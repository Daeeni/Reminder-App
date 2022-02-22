#include "Manager.hpp"
#include <iostream>

using namespace Reminder::Core;
using namespace Reminder::Core::Model;
using namespace Reminder::Api::Parser;
using namespace Reminder::Repository;
using namespace std;

Manager::Manager(ParserIf &givenParser, RepositoryIf &givenRepository)
    : parser(givenParser), repository(givenRepository) {
}

Manager::~Manager() {
}

std::string Manager::getBoard() {
    Board board = repository.getBoard();

    return parser.convertToApiString(board);
}

std::string Manager::getLists() {
    std::vector<List> lists = repository.getLists();

    return parser.convertToApiString(lists);
}

std::string Manager::getList(int listid) {

    std::optional<List> list = repository.getList(listid);
    if (list) {
        return parser.convertToApiString(list.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string Manager::postList(std::string request) {

    int const dummyId = -1;
    std::optional<List> parsedListOptional = parser.convertListToModel(dummyId, request);
    if (false == parsedListOptional.has_value()) {
        return parser.getEmptyResponseString();
    }

    List parsedList = parsedListOptional.value();

    std::optional<List> postedList = repository.postList(parsedList.getvalue());

    if (postedList) {
        return parser.convertToApiString(postedList.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string Manager::putList(int listid, std::string request) {

    std::optional<List> parsedListOptional = parser.convertListToModel(listid, request);

    if (false == parsedListOptional.has_value()) {
        return parser.getEmptyResponseString();
    }
    List list = parsedListOptional.value();
    std::optional<List> putList = repository.putList(listid, list.getvalue());

    if (putList) {
        return parser.convertToApiString(putList.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string Manager::getItems(int listid) {
    std::vector<Item> items = repository.getItems(listid);

    return parser.convertToApiString(items);
}

std::string Manager::getItem(int listid, int itemid) {

    std::optional<Item> item = repository.getItem(listid, itemid);

    if (item) {
        return parser.convertToApiString(item.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string Manager::postItem(int listid, std::string request) {
    int const dummyId = -1;
    std::optional parsedItemOptional = parser.convertItemToModel(dummyId, request);
    if (false == parsedItemOptional.has_value()) {
        return parser.getEmptyResponseString();
    }

    Item item = parsedItemOptional.value();
    std::optional<Item> postedItem = repository.postItem(listid, item.getvalue(), item.getdate(), item.getflag());
    if (postedItem) {
        return parser.convertToApiString(postedItem.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

std::string Manager::putItem(int listid, int itemid, std::string request) {

    std::optional parsedItemOptional = parser.convertItemToModel(itemid, request);
    if (false == parsedItemOptional.has_value()) {
        return parser.getEmptyResponseString();
    }

    Item item = parsedItemOptional.value();
    std::optional<Item> putItem = repository.putItem(listid, itemid, item.getvalue(), item.getdate(), item.getflag());

    if (putItem) {
        return parser.convertToApiString(putItem.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

void Manager::deleteItem(int listid, int itemid) {
    repository.deleteItem(listid, itemid);
}
