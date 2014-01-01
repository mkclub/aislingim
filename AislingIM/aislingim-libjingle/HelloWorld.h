#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#include <string>

#ifdef AISLINGIMLIBJINGLE_EXPORTS
#define AISLINGIMLIBJINGLE_API __declspec(dllexport)
#else
#define AISLINGIMLIBJINGLE_API __declspec(dllimport)
#endif

AISLINGIMLIBJINGLE_API std::string hello(std::string name);


#endif // HELLO_WORLD_H
