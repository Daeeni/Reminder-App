#include "Item.hpp"

using namespace Reminder::Core::Model;

Item::Item(int givenid, std::string givenvalue, bool givenflag, std::string givendate)
    : id(givenid), value(givenvalue), flagged(givenflag), date(givendate) {}

int Item::getid() const {
    return id;
}

std::string Item::getvalue() const {
    return value;
}

bool Item::getflag() const {
    return flagged;
}

std::string Item::getdate() const {
    return date;
}

void Item::setid(int givenid) {
    id = givenid;
}

void Item::setvalue(std::string givenvalue) {
    value = givenvalue;
}

void Item::setflag(bool givenflag) {
    flagged = givenflag;
}

void Item::setdate(std::string givendate) {
    date = givendate;
}
