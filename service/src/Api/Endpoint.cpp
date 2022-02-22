#include "Endpoint.hpp"

#include <iostream>

using namespace Reminder::Api;
using namespace Reminder::Core;
using namespace crow;
using namespace std;

Endpoint::Endpoint(SimpleApp &givenApp, Manager &givenManager) : app(givenApp), manager(givenManager) {

    registerRoutes();
}

Endpoint::~Endpoint() {
}

void Endpoint::registerRoutes() {
    CROW_ROUTE(app, "/api/board")
    ([this](const request &req, response &res) {
        std::string jsonBoards = manager.getBoard();
        res.write(jsonBoards);
        res.end();
    });

    CROW_ROUTE(app, "/api/board/lists")
        .methods("GET"_method, "POST"_method)([this](const request &req, response &res) {
            std::string jsonLists;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonLists = manager.getLists();
                break;
            }
            case HTTPMethod::Post: {
                jsonLists = manager.postList(req.body);
                res.code = 201;
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonLists);
            res.end();
        });

    CROW_ROUTE(app, "/api/board/lists/<int>")
        .methods("GET"_method, "PUT"_method)([this](const request &req, response &res, int listid) {
            std::string jsonList = "{}";

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonList = manager.getList(listid);
                break;
            }
            case HTTPMethod::Put: {
                jsonList = manager.putList(listid, req.body);
                break;
            }
            default: {
                break;
            }
                // keine DELETE weil listen nicht löschbar sein sollen
            }

            res.write(jsonList);
            res.end();
        });

    CROW_ROUTE(app, "/api/board/lists/<int>/items")
        .methods("GET"_method, "POST"_method)([this](const request &req, response &res, int listid) {
            std::string jsonItem;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonItem = manager.getItems(listid);
                break;
            }
            case HTTPMethod::Post: {
                jsonItem = manager.postItem(listid, req.body);
                res.code = 201;
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonItem);
            res.end();
        });

    CROW_ROUTE(app, "/api/board/lists/<int>/items/<int>")
        .methods("GET"_method, "PUT"_method, "DELETE"_method)([this](const request &req, response &res, int listid, int itemid) {
            std::string jsonItem;

            switch (req.method) {
            case HTTPMethod::Get: {
                jsonItem = manager.getItem(listid, itemid);
                break;
            }
            case HTTPMethod::Put: {
                jsonItem = manager.putItem(listid, itemid, req.body);
                break;
            }
            case HTTPMethod::Delete: {
                manager.deleteItem(listid, itemid);
                break;
            }
            default: {
                break;
            }
            }

            res.write(jsonItem);
            res.end();
        });
}
