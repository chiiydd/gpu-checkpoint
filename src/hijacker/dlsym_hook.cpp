#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "dlsym_hook.h"
#include "cuda_hook.h"
cuGetProcAddress_t realCuGetProcAddress=nullptr;

#define FUNC_ATTR_VISIBLE __attribute__((visibility("default")))
FUNC_ATTR_VISIBLE void *dlsym(void *handle, const char *symbol) {
    printf(" --- Intercepted dlsym: Requesting symbol %s\n", symbol);

    FuncTypeDlsym real_dlsym = NULL;
    if (real_dlsym == NULL)
        real_dlsym = (FuncTypeDlsym) dlvsym(RTLD_NEXT, "dlsym", "GLIBC_2.2.5");


    if (strcmp(symbol, "cuGetProcAddress_v2") == 0) {
        printf(" --- Applying dlsym hook: Requesting symbol %s\n", symbol);
        if (realCuGetProcAddress==nullptr){
            realCuGetProcAddress = (cuGetProcAddress_t) real_dlsym(handle, "cuGetProcAddress_v2");
        }
        return (void *) &cuGetProcAddress;
    }
    /* my target binary is even asking for dlsym() via dlsym()... */
    if (!strcmp(symbol, "dlsym"))
        return (void *) dlsym;

    return real_dlsym(handle, symbol);
}



