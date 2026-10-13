/* func_ov145_02299bd0 @ 0x02299bd0, 0x70 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov145_02299668(char *, int);
extern void func_ov145_02299aac(char *);
extern int func_020b9bbc(const char *, const char *, int, int, int);
extern void func_ov145_02299648(char *, int);
extern void func_ov145_02299c40(char *);

void func_ov145_02299bd0(char *arg)
{
    if (func_ov145_02299668(arg, 8)) {
        func_ov145_02299aac(arg);
    }

    if (func_ov145_02299668(arg, 2)) {
        if (func_020b9bbc(arg + 0xafc, arg + 0x1cc6, 6, 0x800, 0)) {
            func_ov145_02299648(arg, 2);
        }
    }

    if (func_ov145_02299668(arg, 4)) {
        func_ov145_02299648(arg, 4);
        func_ov145_02299c40(arg);
    }
}
