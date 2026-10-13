/* func_0209549c @ 0x0209549c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int d[12];
} BigT;

extern char *func_02096718(int);

void func_0209549c(BigT *dst, int src)
{
    *dst = *(BigT *) (func_02096718(src) + 0x698);
}
