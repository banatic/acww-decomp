/* func_ov146_02299e28 @ 0x02299e28, 0x74 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov146_02299670(char *p, int opt);
extern int func_ov146_02299650(char *p, int opt);
extern int func_020b9bbc(char *dst, char *src, int size, int mode, int flag);
extern int func_020b9b6c(char *dst, char *src, int size, int mode);

void func_ov146_02299e28(char *p)
{
    if (func_ov146_02299670(p, 2)) {
        if (func_020b9bbc(p + 0x1ea0, p + 0x0d8a, 4, 0x800, 0)) {
            func_ov146_02299650(p, 2);
        }
    }
    if (func_ov146_02299670(p, 8)) {
        if (func_020b9b6c(p + 0x1ec4, p + 0x15aa, 4, 7)) {
            func_ov146_02299650(p, 8);
        }
    }
}
