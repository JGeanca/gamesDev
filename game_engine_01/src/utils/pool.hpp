#ifndef POOL_HPP
#define POOL_HPP

#include <vector>

template <typename TComponent>
class Pool {
 private:
  std::vector<TComponent> data;
};

#endif