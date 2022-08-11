#include "InstancePointers.hpp"

intptr_t InstancePointers::write_func_ptr;
intptr_t InstancePointers::write_before_read_func_ptr;
intptr_t InstancePointers::read_func_ptr;

void InstancePointers::setWriteFuncPtr(intptr_t ptr) {
    InstancePointers::write_func_ptr = ptr;
}

void InstancePointers::setWriteBeforeReadFuncPtr(intptr_t ptr) {
    InstancePointers::write_func_ptr = ptr;
}

void InstancePointers::setReadFuncPtr(intptr_t ptr) {
    InstancePointers::read_func_ptr = ptr;
}

intptr_t InstancePointers::getWriteFuncPtr() {
    return InstancePointers::write_func_ptr;
}

intptr_t InstancePointers::getWriteBeforeReadFuncPtr() {
    return InstancePointers::write_func_ptr;
}

intptr_t InstancePointers::getReadFuncPtr() {
    return InstancePointers::read_func_ptr;
}
