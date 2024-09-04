// debug.h
#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>

#ifdef DEBUG_FLAG  // if the DEBUG_FLAG is defined (make run -d)
#define DEBUG_MSG(msg) debug::printDebugMessage(msg)  // enable debug messages
#else  // if the DEBUG_FLAG is not defined (make run)
// disable debug messages
#define DEBUG_MSG(msg) \
  do {                 \
  } while (false)
#endif

namespace debug {
inline void printDebugMessage(const std::string& msg) {
  std::cout << msg << std::endl;
}
}  // namespace debug

#endif  // DEBUG_H
