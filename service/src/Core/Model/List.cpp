#include "List.hpp"

using namespace Reminder::Core::Model;

List::List(int givenid, std::string givenvalue)
    : id(givenid), value(givenvalue) {}

int List::getid() const {
    return id;
}

std::string List::getvalue() const {
    return value;
}

std::vector<Item> List::getitems() const {
    return items;
}

void List::setid(int givenid) {
    id = givenid;
}

void List::setvalue(std::string givenvalue) {
    value = givenvalue;
}

void List::additem(Item &givenitem) {
    items.push_back(givenitem);
}