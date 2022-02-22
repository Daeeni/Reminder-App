#pragma once

#include "Api/Parser/ParserIf.hpp"
#include "Repository/RepositoryIf.hpp"

namespace Reminder {
namespace Core {
class Manager {
    private:
        Reminder::Repository::RepositoryIf &repository;
        Reminder::Api::Parser::ParserIf &parser;

    public:
        Manager(Reminder::Api::Parser::ParserIf &givenParser, Reminder::Repository::RepositoryIf &givenRepository);
        ~Manager();

        std::string getBoard();
        std::string getLists();
        std::string getList(int listid);
        std::string postList(std::string request);
        std::string putList(int listid, std::string request);

        std::string getItems(int listid);
        std::string getItem(int listid, int itemid);
        std::string postItem(int listid, std::string request);
        std::string putItem(int listid, int itemid, std::string request);
        void deleteItem(int listid, int itemid);
};
} //namespace Core
} //namespace Reminder