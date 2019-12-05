//
// Created by andrey on 04.12.2019.
//

#ifndef K_ON_TCP_SERVER_H
#define K_ON_TCP_SERVER_H

#include <boost/asio.hpp>
#include <iostream>

#define READ_UNTIL_DELIM "\n"

class TcpServer {
public:
    TcpServer(unsigned short port);
    void start_server();

protected:
    unsigned short port_;
    boost::asio::io_service service_;
    boost::asio::ip::tcp::acceptor acceptor_;

protected:
    void on_accept(boost::asio::ip::tcp::socket sock);
    std::string to_string(boost::asio::streambuf &buf);
    virtual std::string handle_request(const std::string &request);  // Если не переопределить, то возвращает request
};


#endif  // K_ON_TCP_SERVER_H
