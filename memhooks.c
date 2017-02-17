#include <stdio.h>
#include <stdlib.h>
#include "rtsym.h"

#define __USE_GNU
#include <dlfcn.h>

#define CHECK_FOUND(var) if (var == NULL) { fprintf(stderr, "Error in dlsym(" #var "): %s\n", dlerror()); exit(1); }
#define CHECK_OPTIONAL(var) if (var == NULL) { fprintf(stderr, "Error in dlsym(" #var "): %s\n", dlerror()); }
#define LOG_ALLOC(start,end) if (start) fprintf(stderr, "memhook-alloc %p %p %p\n", start, end, __builtin_return_address(0))
#define LOG_FREE(start) if (start) fprintf(stderr, "memhook-free %p %p\n", start, __builtin_return_address(0))

static malloc_t realMalloc = NULL;
static realloc_t realRealloc = NULL;
static calloc_t realCalloc = NULL;
static free_t realFree = NULL;
static memalign_t realMemalign = NULL;

static malloc_t realNew = NULL;
static malloc_t realNewNoThrow = NULL;
static free_t realDelete = NULL;
static free_t realDeleteNoThrow = NULL;

void __register_memhooks() {
    realMalloc = rtsym_resolve("malloc");
    CHECK_FOUND(realMalloc);
    realRealloc = rtsym_resolve("realloc");
    CHECK_FOUND(realRealloc);
    realCalloc = rtsym_resolve("calloc");
    CHECK_FOUND(realCalloc);
    realFree = rtsym_resolve("free");
    CHECK_FOUND(realFree);
    realMemalign = rtsym_resolve("memalign");
    CHECK_FOUND(realMemalign);
    realNew = rtsym_resolve(M2STR(CXX_SYM_NEW));
    CHECK_OPTIONAL(realNew);
    realNewNoThrow = rtsym_resolve(M2STR(CXX_SYM_NEW_NOTHROW));
    CHECK_OPTIONAL(realNewNoThrow);
    realDelete = rtsym_resolve(M2STR(CXX_SYM_DELETE));
    CHECK_OPTIONAL(realDelete);
    realDeleteNoThrow = rtsym_resolve(M2STR(CXX_SYM_DELETE_NOTHROW));
    CHECK_OPTIONAL(realDeleteNoThrow);
}

void *malloc(size_t size) {
    if (realMalloc == NULL) {
        __register_memhooks();
    }

    void *p = realMalloc(size);
    LOG_ALLOC(p, p + size);
    return p;
}

void* realloc(void* ptr, size_t size) {
    if (realRealloc == NULL) {
        __register_memhooks();
    }

    LOG_FREE(ptr);
    void *p = realRealloc(ptr, size);
    LOG_ALLOC(p, p + size);
    return p;
}

void* calloc(size_t count, size_t size) {
    if (realCalloc == NULL) {
        __register_memhooks();
    }

    void *p = realCalloc(count, size);
    LOG_ALLOC(p, p + (count * size));
    return p;
}

void free(void* ptr) {
    if (realFree == NULL) {
        __register_memhooks();
    }

    LOG_FREE(ptr);
    realFree(ptr);
}


void* memalign(size_t boundary, size_t size) {
    if (realMemalign == NULL) {
        __register_memhooks();
    }

    void* p = realMemalign(boundary, size);
    LOG_ALLOC(p, p + size);
    return p;
}

void* CXX_SYM_NEW(size_t size) {
    if (realNew == NULL) {
        __register_memhooks();
    }

    void* p = realNew(size);
    LOG_ALLOC(p, p + size);
    return p;
}

void* CXX_SYM_NEW_NOTHROW(size_t size) {
    if (realNewNoThrow == NULL) {
        __register_memhooks();
    }

    void* p = realNewNoThrow(size);
    LOG_ALLOC(p, p + size);
    return p;
}

void CXX_SYM_DELETE(void *ptr) {
    if (realDelete == NULL) {
        __register_memhooks();
    }

    LOG_FREE(ptr);
    realDelete(ptr);
}

void CXX_SYM_DELETE_NOTHROW(void *ptr) {
    if (realDeleteNoThrow == NULL) {
        __register_memhooks();
    }

    LOG_FREE(ptr);
    realDeleteNoThrow(ptr);
}
