/* func_ov122_022a15b8 @ 0x022a15b8, 0x160 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

#define U8(p) (*(unsigned char *) (p))
#define P(a) (*(char **) ((a) + 0xbc))

extern void func_ov122_0229efd8(char *, int);
extern void func_0206e114(char *, char *, char *);
extern void func_0206e03c(char *, char *, int);
extern void func_0206dff8(char *, char *);
extern int func_ov122_0229f958(char *);
extern void func_0206dfe0(char *, int, int, int);
extern int func_0206e224(char *);
extern void func_0206df58(char *, int, int, int);
extern void func_0206df40(char *, int, int, int);
extern void func_ov122_022a14c0(char *);

void func_ov122_022a15b8(char *a, int flag, int v)
{
    int base, n, mode;

    func_ov122_0229efd8(a, 0x1000);
    if (flag != 0) {
        func_0206e114(a + 0x3ce8, P(a), a + 0x41e0);
        func_0206e03c(a + 0x3ce8, P(a) + 0x58, v);
        func_0206dff8(a + 0x3ce8, P(a) + 0xd8);
    } else {
        switch (U8(a + 0xaa)) {
            case 0:
            case 1:
                func_0206e114(a + 0x3ce8, P(a), a + 0x41e0);
                break;
            case 2:
                func_0206e03c(a + 0x3ce8, P(a) + 0x58, v);
                break;
            case 3:
                func_0206dff8(a + 0x3ce8, P(a) + 0xd8);
                break;
        }
    }
    if (func_ov122_0229f958(a)) {
        mode = 0;
        if (U8(a + 0xad) > U8(a + 0xae)) {
            base = U8(a + 0xae);
            n = U8(a + 0xad) - U8(a + 0xae);
        } else {
            base = U8(a + 0xad);
            n = U8(a + 0xae) - U8(a + 0xad);
        }
    } else {
        mode = 1;
        n = 0;
    }
    if (n != 0) {
        switch (U8(a + 0xaa)) {
            case 0:
                func_0206dfe0(a + 0x3ce8, base, n, mode);
                break;
            case 1: {
                int off = base + (U8(P(a) + 0xf8) + func_0206e224(a + 0x3ce8));
                func_0206dfe0(a + 0x3ce8, off, n, mode);
                break;
            }
            case 2:
                func_0206df58(a + 0x3ce8, base, n, mode);
                break;
            case 3:
                func_0206df40(a + 0x3ce8, base, n, mode);
                break;
        }
    }
    func_ov122_022a14c0(a);
}
