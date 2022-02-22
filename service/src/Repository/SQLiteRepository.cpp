#include "SQLiteRepository.hpp"
#include <filesystem>
#include <string.h>

using namespace Reminder::Repository;
using namespace Reminder::Core::Model;
using namespace std;

#ifdef RELEASE_SERVICE
string const SQLiteRepository::databaseFile = "./data/Reminder.db";
#else
string const SQLiteRepository::databaseFile = "../data/Reminder.db";
#endif

SQLiteRepository::SQLiteRepository() : database(nullptr) {

    std::string databaseDirectory = filesystem::path(databaseFile).parent_path().string();

    if (filesystem::is_directory(databaseDirectory) == false) {
        filesystem::create_directory(databaseDirectory);
    }

    int result = sqlite3_open(databaseFile.c_str(), &database);

    if (SQLITE_OK != result) {
        cout << "Cannot open databes: " << sqlite3_errmsg(database) << endl;
    }

    initialize();
}

SQLiteRepository::~SQLiteRepository() {
    sqlite3_close(database);
}

void SQLiteRepository::initialize() {
    int result = 0;
    char *errorMessage = nullptr;

    std::string sqlCreateTableList =
        "create table if not exists List("
        "id integer not null primary key autoincrement,"
        "value text not null);";

    std::string sqlCreateTableItem =
        "create table if not exists item("
        "id integer not null primary key autoincrement,"
        "value text not null,"
        "date text not null,"
        "flagged bit not null,"
        "List_id integer not null,"
        "foreign key (List_id) references List (id));";

    result = sqlite3_exec(database, sqlCreateTableList.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
    result = sqlite3_exec(database, sqlCreateTableItem.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
}

Board SQLiteRepository::getBoard() {

    Board board = Board(boardTitle);
    board.setlists(getLists());
    return board;
}

std::vector<List> SQLiteRepository::getLists() {
    std::vector<List> lists;
    string sqlQueryLists =
        "SELECT * FROM List;";
    int result = 0;
    char *errorMessage = nullptr;
    result = sqlite3_exec(database, sqlQueryLists.c_str(), queryListsCallback, &lists, &errorMessage);
    handleSQLError(result, errorMessage);

    if (SQLITE_OK == result && !lists.empty()) {
        for (List &c : lists) {
            vector<Item> items = getItems(c.getid());
            for (Item &i : items) {
                c.additem(i);
            }
        }
        return lists;
    }
    return {};
}

std::optional<List> SQLiteRepository::getList(int id) {

    std::vector<List> lists;

    string sqlQueryLists =
        "SELECT List.id, List.value, item.id, item.value, item.date, item.flagged from List "
        "left join item on item.List_id = List.id where List.id = " +
        to_string(id) + ";";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQueryLists.c_str(), queryListsCallback, &lists, &errorMessage);
    handleSQLError(result, errorMessage);

    if (lists.size() == 1) {
        return lists.front();
    } else {
        return std::nullopt;
    }
}

std::optional<List> SQLiteRepository::postList(std::string value) {

    string sqlPostItem =
        "INSERT INTO List('value') "
        "VALUES ('" +
        value + "')";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlPostItem.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    if (SQLITE_OK == result) {
        int Listid = sqlite3_last_insert_rowid(database);
        return List(Listid, value);
    }

    return std::nullopt;
}

std::optional<Reminder::Core::Model::List> SQLiteRepository::putList(int id, std::string value) {

    string sqlUpdateList =
        "UPDATE List "
        "SET value = '" +
        value + "' WHERE id = " +
        to_string(id) + ";";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlUpdateList.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    return getList(id);
}

std::vector<Item> SQLiteRepository::getItems(int Listid) {
    std::vector<Item> items;
    string sqlQueryItems =
        "SELECT item.id, item.value, item.date, item.flagged from item "
        "WHERE item.List_id = " +
        to_string(Listid) + ";";
    int result = 0;
    char *errorMessage = nullptr;
    result = sqlite3_exec(database, sqlQueryItems.c_str(), queryItemsCallback, &items, &errorMessage);
    handleSQLError(result, errorMessage);
    if (items.empty())
        return {};
    return items;
}

std::optional<Item> SQLiteRepository::getItem(int Listid, int Itemid) {

    std::vector<Item> items;

    string sqlQueryItems =
        "SELECT item.id, item.value, item.date, item.flagged from item "
        "WHERE item.List_id = " +
        to_string(Listid) + " AND item.id = " + to_string(Itemid) + ";";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlQueryItems.c_str(), queryItemsCallback, &items, &errorMessage);
    handleSQLError(result, errorMessage);

    if (items.size() == 1) {
        return items.front();
    } else {
        return std::nullopt;
    }
}

std::optional<Item> SQLiteRepository::postItem(int Listid, std::string value, std::string date, bool flag) {

    string sqlPostItem =
        "INSERT INTO item ('value', 'date', 'flagged', 'List_id') "
        "VALUES ('" +
        value + "', '" + date + "', ";
    if (flag) {
        sqlPostItem = sqlPostItem + to_string(1);
    } else {
        sqlPostItem = sqlPostItem + to_string(0);
    }
    sqlPostItem = sqlPostItem + ", " + to_string(Listid) + ")";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlPostItem.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    if (SQLITE_OK == result) {
        int Itemid = sqlite3_last_insert_rowid(database);
        return getItem(Listid, Itemid);
    }
    return std::nullopt;
}

std::optional<Reminder::Core::Model::Item> SQLiteRepository::putItem(int Listid, int Itemid, std::string value, std::string date, bool flag) {

    std::string sqlUpdateItem =
        "UPDATE item SET value = '" + value + "', date = '" + date + "', flagged = '";
    if (flag) {
        sqlUpdateItem = sqlUpdateItem + to_string(1) + "' WHERE item.List_id = " + to_string(Listid) + " AND item.id = " + to_string(Itemid) + ";";
    } else {
        sqlUpdateItem = sqlUpdateItem + to_string(0) + "' WHERE item.List_id = " + to_string(Listid) + " AND item.id = " + to_string(Itemid) + ";";
    }

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlUpdateItem.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    return getItem(Listid, Itemid);
}

void SQLiteRepository::deleteItem(int Listid, int Itemid) {
    string sqlQueryItem =
        "DELETE FROM item "
        "WHERE item.List_id = " +
        to_string(Listid) + " AND item.id = " + to_string(Itemid) + ";";

    int result = 0;
    char *errorMessage = nullptr;
    result = sqlite3_exec(database, sqlQueryItem.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
}

Item SQLiteRepository::getItemFromCallback(char **fieldValues, int startIndex) {
    int index = startIndex;
    int Itemid = fieldValues[index] ? atoi(fieldValues[index]) : INVALID_ID;
    index++;
    std::string value = fieldValues[index] ? fieldValues[index] : "";
    index++;
    std::string date = fieldValues[index] ? fieldValues[index] : "";
    index++;
    bool flagged = (atoi(fieldValues[index]) == 0) ? false : true;
    return Item(Itemid, value, flagged, date);
}

List SQLiteRepository::getListFromCallback(char **fieldValues, int startIndex) {
    int index = startIndex;

    int Listid = fieldValues[index] ? atoi(fieldValues[index]) : INVALID_ID;
    index++;

    std::string value = fieldValues[index] ? fieldValues[index] : "";
    index++;

    List list(Listid, value);
    return list;
}

int SQLiteRepository::queryListsCallback(void *data, int numberofLists, char **fieldValues, char **Listnames) {
    vector<List> *lists = static_cast<vector<List> *>(data);
    if (fieldValues == nullptr) {
        return 0;
    }
    List column(stoi(fieldValues[0]), fieldValues[1]);
    lists->push_back(column);
    return 0;
}

int SQLiteRepository::queryItemsCallback(void *data, int numberofLists, char **fieldValues, char **Listnames) {
    vector<Item> *result = static_cast<std::vector<Item> *>(data);
    Item item = getItemFromCallback(fieldValues, 0);
    if (isValid(item.getid())) {
        result->push_back(item);
    }
    return 0;
}

void SQLiteRepository::handleSQLError(int statementResult, char *errorMessage) {

    if (statementResult != SQLITE_OK) {
        cout << "SQL error: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
}
