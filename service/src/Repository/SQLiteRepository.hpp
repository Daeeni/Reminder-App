#pragma once

#include "Repository/RepositoryIf.hpp"
#include "sqlite3.h"

namespace Reminder {
namespace Repository {

class SQLiteRepository : public RepositoryIf {
  private:
    sqlite3 *database;

    void initialize();
    void handleSQLError(int statementResult, char *errorMessage);

    static bool isValid(int id) {
        return id != INVALID_ID;
    }

    static Reminder::Core::Model::Item getItemFromCallback(char **fieldValues, int startIndex);
    static Reminder::Core::Model::List getListFromCallback(char **fieldValues, int startIndex);

    static int queryListsCallback(void *data, int numberofLists, char **fieldValues, char **ListNames);
    static int queryItemsCallback(void *data, int numberofLists, char **fieldValues, char **Listnames);

  public:
    SQLiteRepository();
    virtual ~SQLiteRepository();

    virtual Reminder::Core::Model::Board getBoard();
    virtual std::vector<Reminder::Core::Model::List> getLists();
    virtual std::optional<Reminder::Core::Model::List> getList(int id);
    virtual std::optional<Reminder::Core::Model::List> postList(std::string value);
    virtual std::optional<Reminder::Core::Model::List> putList(int id, std::string value);

    virtual std::vector<Reminder::Core::Model::Item> getItems(int Listid);
    virtual std::optional<Reminder::Core::Model::Item> getItem(int Listid, int itemid);
    virtual std::optional<Reminder::Core::Model::Item> postItem(int Listid, std::string value, std::string date, bool flag);
    virtual std::optional<Reminder::Core::Model::Item> putItem(int Listid, int Itemid, std::string value, std::string date, bool flag);
    virtual void deleteItem(int Listid, int itemid);

    static inline std::string const boardTitle = "Reminder";
    static inline int const INVALID_ID = -1;

    static std::string const databaseFile;
};
} // namespace Repository
} // namespace Reminder
