#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <string>

class Handler {
  public:
    virtual Handler *set_next(Handler *handler) = 0;
    virtual std::string handle(std::string request) = 0;
};

#endif