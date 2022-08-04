#pragma once

#include <cstdint>
typedef void writeFunc(const char*);
typedef void readFunc(const char*);

class InstancePointers {
   private:
    static intptr_t write_func_ptr;
    static intptr_t read_func_ptr;

   public:
    static void setWriteFuncPtr(intptr_t ptr);
    static void setReadFuncPtr(intptr_t ptr);

    static intptr_t getWriteFuncPtr();
    static intptr_t getReadFuncPtr();
};
