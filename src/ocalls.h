#ifdef USE_SGX

#ifdef USE_EDP
/* FIXME: no need for this in upstream where "dont_replace_c_symbols" is off by default */
static inline int printf_sgx(const char *fmt, ...) {
    return 1;
}
#endif

#ifndef USE_EDP
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

extern int u_write_ocall(size_t* retval, size_t fd, const void* buf, size_t nbytes);

static inline int printf_sgx(const char *fmt, ...) {
    va_list ap;
    char buf[BUFSIZ] = {'\0'};
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);

    size_t ret;

    u_write_ocall(&ret, STDOUT_FILENO, buf, strnlen(buf, BUFSIZ));
    return 0;
}
#endif

#endif