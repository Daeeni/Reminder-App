#pragma once

#include "List.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace Reminder {
namespace Core {
namespace Model {

class Board {
  public:
    Board(std::string giventitle);
    ~Board() {}

    std::string gettitle() const;

    std::vector<List> &getlists();
    void setlists(std::vector<List> const &lists);

  private:
    std::string title;
    std::vector<List> lists;
};
} // Namespace Model
} // Namespace Core
} // Namespace Reminder
