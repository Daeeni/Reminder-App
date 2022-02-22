#pragma once

#include "Core/Model/Board.hpp"
#include "optional"

namespace Reminder {
namespace Repository {
class RepositoryIf {
  public:
    virtual ~RepositoryIf() {}

    virtual Reminder::Core::Model::Board getBoard() = 0;
    virtual std::vector<Reminder::Core::Model::List> getLists() = 0;
    virtual std::optional<Reminder::Core::Model::List> getList(int id) = 0;
    virtual std::optional<Reminder::Core::Model::List> postList(std::string value) = 0;
    virtual std::optional<Reminder::Core::Model::List> putList(int id, std::string value) = 0;

    virtual std::vector<Reminder::Core::Model::Item> getItems(int Listid) = 0;
    virtual std::optional<Reminder::Core::Model::Item> getItem(int Listid, int itemid) = 0;
    virtual std::optional<Reminder::Core::Model::Item> postItem(int Listid, std::string value, std::string date, bool flag) = 0;
    virtual std::optional<Reminder::Core::Model::Item> putItem(int Listid, int Itemid, std::string value, std::string date, bool flag) = 0;
    virtual void deleteItem(int Listid, int itemid) = 0;
};
} // namespace Repository
} // namespace Reminder
