#include "Board.hpp"

using namespace Reminder::Core::Model;

Board::Board(std::string giventitle) : title(giventitle) {}

std::string Board::gettitle() const {
    return title;
}

std::vector<List> &Board::getlists() {
    return lists;
}

void Board::setlists(std::vector<List> const &lists) {
    this->lists = lists;
}
