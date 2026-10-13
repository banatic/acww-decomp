// Minimal MSL-compatible string.h. mwccarm only treats memcpy, memset, strlen, ... as
// built-ins when they are declared through an #include of a file named string.h.
typedef unsigned long size_t;
extern void *memcpy(void *dst, const void *src, size_t n);
extern void *memset(void *dst, int c, size_t n);
extern void *memmove(void *dst, const void *src, size_t n);
extern int memcmp(const void *a, const void *b, size_t n);
extern unsigned long strlen(const char *s);
extern char *strcpy(char *dst, const char *src);
extern char *strncpy(char *dst, const char *src, size_t n);
extern int strcmp(const char *a, const char *b);
extern int strncmp(const char *a, const char *b, size_t n);
extern char *strcat(char *dst, const char *src);
extern char *strchr(const char *s, int c);
extern char *strstr(const char *s, const char *find);
extern char *strrchr(const char *s, int c);
