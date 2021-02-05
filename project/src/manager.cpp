//
// Created by andrey on 22.11.2019.
//

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

#include "manager.h"
#include "url_parser.h"
#include "json.h"

std::string Manager::handle_request(const std::string &request, const std::string &session) {
    UrlParser url_parser;
    url_parser.parse(request);
    std::string path = url_parser.path();

    try {
        if (path == "/login") {
            return on_auth(url_parser, "login");
        }
        if (path == "/logout") {
            return on_logout(session);
        }
        if (path == "/signup") {
            return on_auth(url_parser, "signup");
        }
        if (path == "/like") {
            return on_like(url_parser, session);
        }
        if (path == "/listen") {
            return on_listen(url_parser, session);
        }
        if (path == "/index") {
            return on_get_page(session, "get_recommendations");
        }
        if (path == "/top") {
            return on_top(session);
        }
        if (path == "/recent") {
            return on_recent(session);
        }
        if (path == "/similarsong") {
            return on_similar_song(url_parser, session);
        }
        if (path == "/update") {
            return on_get_page(session, "update_recommendations");
        }
        if (path == "/history") {
            return on_get_page(session, "get_liked_songs");
        }

        return on_fail(400, "bad request");
    }
    catch (boost::system::system_error const &e) {
        if (e.code() == boost::asio::error::connection_refused) {
            return on_fail(503, "service unavailable");
        } else {
            boost::throw_exception(e);
        }
    }
    catch (boost::property_tree::ptree_bad_path const &e) {
        std::cout << e.what() << std::endl;
        return on_fail(500, "Internal server error");
    }
    catch (boost::property_tree::json_parser_error const &e) {
        std::cout << e.what() << std::endl;
        return on_fail(500, "Internal server error");
    }
}

std::string Manager::on_auth(const UrlParser &url_parser, const std::string &method) {
    if (url_parser.has_parameter("login") && url_parser.has_parameter("password")) {
        std::string login = url_parser.get_parameter("login");
        std::string password = url_parser.get_parameter("password");

        boost::property_tree::ptree root;
        root.put("method", method);
        root.put("login", login);
        root.put("password", password);

        connect(USER_HOST, USER_PORT);
        write(stringify_json(root));  // Отправляем запрос на логин или регистрацию

        std::string answer = read();  // Читаем ответ

        root = parse_to_json(answer);

        if (root.get<int>("status") == 401) {  // Логин или регистрация не прошла
            return answer;
        } else {  // Логин или регистрация прошла успешно
            std::string session = root.get<std::string>("session");  // Сохраняем сессию пользователя

            connect(USER_HOST, USER_PORT);
            root.clear();
            root.put("method", "get_user_id");
            root.put("session", session);
            write(stringify_json(root));

            root = parse_to_json(read());

            int user_id = root.get<int>("user_id");

            root.clear();
            root.put("method", "update_recommendations");
            root.put("user_id", user_id);

            connect(RECOMMENDATION_HOST, RECOMMENDATION_PORT);
            write(stringify_json(root));  // Отправлем запрос на обновление рекоммендаций пользователя

            answer = read();

            root = parse_to_json(answer);

            root.put("session", session);
            root.put("status", 301);
            root.put("page", "index");
            root.put("login", login);

            return stringify_json(root);
        }
    } else {
        return on_fail(400, "bad request, please add get parameters: login and password");
    }
}

std::string Manager::on_logout(const std::string &session) {
    boost::property_tree::ptree root;
    root.put("method", "logout");
    root.put("session", session);

    connect(USER_HOST, USER_PORT);
    write(stringify_json(root));

    return read();
}

std::string Manager::on_listen(const UrlParser &url_parser, const std::string &session) {
    if (url_parser.has_parameter("song_id")) {
        std::string song_id = url_parser.get_parameter("song_id");
        std::string next = url_parser.get_parameter("next");

        boost::property_tree::ptree root;
        root.put("method", "listen");
        root.put("song_id", song_id);
        root.put("session", session);

        connect(USER_HOST, USER_PORT);
        write(stringify_json(root));

        std::string answer = read();
        root = parse_to_json(answer);

        if (root.get<int>("status") == 301) {
            root.put("page", next);
            return stringify_json(root);
        } else {
            return answer;
        }

    } else {
        return on_fail(400, "bad request, please add get parameter: song_id and next");
    }
}

std::string Manager::on_like(const UrlParser &url_parser, const std::string &session) {
    if (url_parser.has_parameter("song_id") && url_parser.has_parameter("like")) {
        std::string song_id = url_parser.get_parameter("song_id");
        std::string like = url_parser.get_parameter("like");
        std::string next = url_parser.get_parameter("next");

        boost::property_tree::ptree root;
        root.put("method", "like");
        root.put("song_id", song_id);
        root.put("like", like);
        root.put("session", session);

        connect(USER_HOST, USER_PORT);
        write(stringify_json(root));

        std::string answer = read();
        root = parse_to_json(answer);

        if (root.get<int>("status") == 301) {
            root.put("page", next);
            return stringify_json(root);
        } else {
            return answer;
        }
    } else {
        return on_fail(400, "bad request, please add get parameter: song_id, like and next");
    }
}

std::string Manager::on_get_page(const std::string &session, const std::string &method) {
    boost::property_tree::ptree root;
    root.put("method", "get_user_id");
    root.put("session", session);

    connect(USER_HOST, USER_PORT);
    write(stringify_json(root));  // Отправляем запрос на получение логина

    std::string answer = read();  // Читаем ответ

    root = parse_to_json(answer);

    if (root.get<int>("status") == 403) {  // Сессия неверная
        root.put("page", "login");
        return stringify_json(root);
    } else {  // Получение лоигина прошло успешно
        std::string login = root.get<std::string>("login");  // Сохраняем логин пользователя
        int user_id = root.get<int>("user_id");  // Сохраняем id пользователя

        root.clear();
        root.put("method", method);
        root.put("user_id", user_id);

        connect(RECOMMENDATION_HOST, RECOMMENDATION_PORT);
        write(stringify_json(root));  // Отправлем запрос на обновление или получение рекоммендаций пользователя

        answer = read();

        root = parse_to_json(answer);
        root.put("login", login);
        root.put("page", get_page(method));

        return stringify_json(root);
    }
}

std::string Manager::on_top(const std::string &session) {
    boost::property_tree::ptree root;
    root.put("method", "get_popular");

    connect(RECOMMENDATION_HOST, RECOMMENDATION_PORT);
    write(stringify_json(root));

    root = parse_to_json(read());
    add_login(root, session);
    root.put("page", "top");
    return stringify_json(root);
}

std::string Manager::on_recent(const std::string &session) {
    boost::property_tree::ptree root;
    root.put("method", "get_new");

    connect(RECOMMENDATION_HOST, RECOMMENDATION_PORT);
    write(stringify_json(root));

    root = parse_to_json(read());
    add_login(root, session);
    root.put("page", "recent");
    return stringify_json(root);
}

std::string Manager::on_similar_song(const UrlParser &url_parser, const std::string &session) {
    if (url_parser.has_parameter("song_id")) {
        std::string song_id = url_parser.get_parameter("song_id");

        boost::property_tree::ptree root;
        root.put("method", "get_similar");
        root.put("song_id", song_id);

        connect(RECOMMENDATION_HOST, RECOMMENDATION_PORT);
        write(stringify_json(root));


        root = parse_to_json(read());
        add_login(root, session);
        root.put("page", "similar_song");
        return stringify_json(root);
    } else {
        return on_fail(400, "bad request, please add get parameter: song_id");
    }
}

void Manager::add_login(boost::property_tree::ptree &root, const std::string &session) {
    boost::property_tree::ptree request;
    request.put("method", "get_user_login");
    request.put("session", session);

    connect(USER_HOST, USER_PORT);
    write(stringify_json(request));

    request = parse_to_json(read());

    if (request.get<int>("status") == 200) {
        root.put("login", request.get<std::string>("login"));
    } else {
        root.put("login", "");
    }
}

std::string Manager::get_method(const std::string &next) {
    if (next == "/top") {
        return "get_popular";
    } else if (next == "/index") {
        return "get_recommendations";
    } else if (next == "/recent") {
        return "get_new";
    }
}

std::string Manager::get_page(const std::string &method) {
    if (method == "get_popular") {
        return "top";
    } else if (method == "get_recommendations" || method == "update_recommendations") {
        return "index";
    } else if (method == "get_new") {
        return "recent";
    } else if (method == "get_liked_songs") {
        return "history";
    }
}
