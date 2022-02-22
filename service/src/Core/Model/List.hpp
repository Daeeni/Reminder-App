#pragma once

#include "Item.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace Reminder {
namespace Core {
namespace Model {

class List {
  public:
    List(int givenid, std::string givenvalue);
    ~List(){};

    int getid() const;
    std::string getvalue() const;
    std::vector<Item> getitems() const;

    void setid(int givenid);
    void setvalue(std::string givenvalue);
    void additem(Item &givenitem);

  private:
    int id;
    std::string value;
    std::vector<Item> items;
};
} // Namespace Model
} // Namespace Core
} // Namespace Reminder
