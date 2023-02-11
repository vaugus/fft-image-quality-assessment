#ifndef ABSTRACT_HANDLER_HPP
#define ABSTRACT_HANDLER_HPP

#include "handler.hpp"

class AbstractHandler : public Handler {
  private:
    Handler *next;

  public:
    AbstractHandler() : next(nullptr) {}

    Handler *set_next(Handler *handler) override {
      this->next = handler;
      return handler;
    }

    std::string handle(std::string request) override {
      if (this->next) return this->next->handle(request);

      return {};
    }
};

#endif