#ifndef BUILDER_HPP
#define BUILDER_HPP

template <typename T>
class Builder {
  public:
    static T builder() { return {}; }
    T & build() { return static_cast<T&>(*this); }
};

#endif
