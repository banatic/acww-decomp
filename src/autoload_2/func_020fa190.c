/* func_020fa190 @ 0x020fa190, 0x74 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern char *func_020ff8a8(char *);
extern void func_020fb640(char *, int, int);
extern void func_020ff8ec(char *, char *);

char *func_020fa190(char *p1, int p2, int p3)
{
    char *result = 0;
    char *t;
    if (*(unsigned int *) (p1 + 12) != 0) {
        t = func_020ff8a8(p1 + 12);
        result = t;
        func_020fb640(t, *(unsigned int *) (p1 + 28) + (p2 << 5), p3);
        func_020ff8ec(p1 + 4, t);
        if (((*(unsigned int *) (*((char **) (*((char **) (t + 0x18)))))) << 17) >> 31) {
            result = 0;
        }
    }
    return result;
}
