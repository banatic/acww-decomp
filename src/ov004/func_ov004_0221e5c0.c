/* func_ov004_0221e5c0 @ 0x0221e5c0, 0x70 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c0e0(void *p);
extern int func_0201c040(void *p, int *a, int *b);
extern int func_020a7278(void);
extern void func_0201c054(void *p, int a, int b, int c);
extern int func_ov004_0221eb44(void *p, void *q);
extern void func_ov004_0221eb6c(void *p, void *q, int a);
extern char *data_020ccf94;

int func_ov004_0221e5c0(void *unused, char *o)
{
    int x;
    int y;
    if (func_0201c0e0(o) != 0) {
        x = 4;
        y = 4;
        if (func_0201c040(o, &x, &y) != 0) {
            if (x == 4) {
                if (func_020a7278() != 0) {
                    func_0201c054(o, 1, *(int *) (data_020ccf94 + 0x64), 4);
                    if (func_ov004_0221eb44(o + 0x8a0, o) == 0) {
                        func_ov004_0221eb6c(o + 0x8a0, o, 0);
                    }
                }
            }
        }
    }
    return 0;
}
