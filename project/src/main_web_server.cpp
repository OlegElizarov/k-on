#include <thread>
#include <iostream>
#include <boost/beast/http/parser.hpp>
#include <boost/beast/http.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "web_server.h"

int main(int argc, char *argv[]) {

    std::cout << "main thread is " << pthread_self() << std::endl;

    if (argc == 2)
    {
        Web_server serv(argv[1]);
        serv.start();
    }
    else{
        Web_server serv;
        serv.start();
    }

    return 0;
}

//strtoi in start
// char buf[1024]??? why?? char *buf = new char[1024]
