#include <stdio.h>
#include <stdlib.h>
#include "rtsym.h"

#define __USE_GNU
#include <dlfcn.h>

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
    realRealloc = rtsym_resolve("realloc");
    realCalloc = rtsym_resolve("calloc");
    realFree = rtsym_resolve("free");
    realMemalign = rtsym_resolve("memalign");
    realNew = rtsym_resolve(M2STR(CXX_SYM_NEW));
    realNewNoThrow = rtsym_resolve(M2STR(CXX_SYM_NEW_NOTHROW));
    realDelete = rtsym_resolve(M2STR(CXX_SYM_DELETE));
    realDeleteNoThrow = rtsym_resolve(M2STR(CXX_SYM_DELETE_NOTHROW));

    if (realMalloc == NULL || realRealloc == NULL || realCalloc == NULL || realFree == NULL
        || realMemalign == NULL || realNew == NULL || realNewNoThrow == NULL || realDelete == NULL
        || realDeleteNoThrow == NULL)
    {
        fprintf(stderr, "Error in dlsym: %s\n", dlerror());
        exit(1);
    }
}

void *malloc(size_t size) {
    if (realMalloc == NULL) {
        __register_memhooks();
    }

    void *p = realMalloc(size);
    if (p) {
        fprintf(stderr, "alloc %p %p\n", p, p + size);
    }
    return p;
}

void* realloc(void* ptr, size_t size) {
    if (realRealloc == NULL) {
        __register_memhooks();
    }

    if (ptr) {
        fprintf(stderr, "free %p\n", ptr);
    }
    void *p = realRealloc(ptr, size);
    if (p) {
        fprintf(stderr, "alloc %p %p\n", p, p + size);
    }
    return p;
}

void* calloc(size_t count, size_t size) {
    if (realCalloc == NULL) {
        __register_memhooks();
    }

    void *p = realCalloc(count, size);
    if (p) {
        fprintf(stderr, "alloc %p %p\n", p, p + (count * size));
    }
    return p;
}

void free(void* ptr) {
    if (realFree == NULL) {
        __register_memhooks();
    }

    if (ptr) {
        fprintf(stderr, "free %p\n", ptr);
    }
    realFree(ptr);
}


void* memalign(size_t boundary, size_t size) {
    if (realMemalign == NULL) {
        __register_memhooks();
    }

    void* p = realMemalign(boundary, size);
    if (p) {
        fprintf(stderr, "alloc %p %p\n", p, p + size);
    }
    return p;
}

void* CXX_SYM_NEW(size_t size) {
    if (realNew == NULL) {
        __register_memhooks();
    }

    void* p = realNew(size);
    if (p) {
        fprintf(stderr, "alloc %p %p\n", p, p + size);
    }
    return p;
}

void* CXX_SYM_NEW_NOTHROW(size_t size) {
    if (realNewNoThrow == NULL) {
        __register_memhooks();
    }

    void* p = realNewNoThrow(size);
    if (p) {
        fprintf(stderr, "alloc %p %p\n", p, p + size);
    }
    return p;
}

void CXX_SYM_DELETE(void *ptr) {
    if (realDelete == NULL) {
        __register_memhooks();
    }

    if (ptr) {
        fprintf(stderr, "free %p\n", ptr);
    }
    realDelete(ptr);
}

void CXX_SYM_DELETE_NOTHROW(void *ptr) {
    if (realDeleteNoThrow == NULL) {
        __register_memhooks();
    }

    if (ptr) {
        fprintf(stderr, "free %p\n", ptr);
    }
    realDeleteNoThrow(ptr);
}
