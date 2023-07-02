/**
 * @file top.h
 * @author Krisna Pranav
 * @brief TOP
 * @version 1.0
 * @date 2023-07-02
 * 
 * @copyright Copyright (c) 2023 Krisna Pranav, zenithlangofficial developers
 * 
 */

#pragma once

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <cstring>
#include <new>

#ifndef ZENITH_DEBUG
#include <typeinfo>
#endif

#if defined(PROF)
#define ZENITH_DEPLOY
#endif

namespace Zenith {
    extern bool throwing_new_allowed;

    #ifdef ASSERT
    #undef ASSERT
    #endif

    #ifdef ZENITH_DEBUG
    void* tracing_malloc(size_t size, const char* file, int line);

    void* tracing_realloc(void* ptr, size_t size, const char* file, int line);

    void* tracing_free(void* ptr, const char* file, int line);

    class newMarker {
    public:
        newMarker(char const* file, int line) 
            : file(file)
            , line(line)
        {}

        char const* const file;
        int const line;
    };

    void trace_new(void* p, const newMarker& record, char const* name);

    template<class T>inline T* operator*(const newMarker& mark, T* p) {
        trace_new(p, mark, typeid(T).name());
        return p;
    }
    #endif 

    class noAllocationScope{
    public:
        ~noAllocationScope() {}
    };

    class AllowThrowingNew {
    public:
        AllowThrowingNew() {
            old_throwing_new_allowed = throwing_new_allowed;
            throwing_new_allowed = true;
        }

        ~AllowThrowingNew() {
            throwing_new_allowed = old_throwing_new_allowed;
        }

    private:
        bool  old_throwing_new_allowed;
    };

    namespace Compiler {
        class ProgrammBuilder;
    }

    class Array;
    class ByteArray;
    class Double;
    class HeapObject;
    class Instance;
    class LargeInteger;
    class Object;
    class Profile;
    class Smi;
    class Stack;
    class String;
    class Task;
    
}