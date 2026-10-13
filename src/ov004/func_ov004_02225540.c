/* func_ov004_02225540 @ 0x02225540, 0x7c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201c0e0(void *self);
extern int func_0201c040(void *self, int *a, int *b);
extern char *data_020ccf94;
extern void func_0201c054(void *self, int a, int b, int c);
extern void func_ov004_022256ec(void *self, int a);
extern int func_020a7278(void);

int func_ov004_02225540(char *self)
{
    int a, b;

    if (func_0201c0e0(self) != 0) {
        a = 4;
        b = 4;
        if (func_0201c040(self, &a, &b) != 0 && a == *(int *) (data_020ccf94 + 0x64) && a == b) {
            func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), *(int *) (data_020ccf94 + 0x64));
            func_ov004_022256ec(self, 1);
        } else if (func_020a7278() != 0 && b == 4) {
            func_0201c054(self, 1, *(int *) (data_020ccf94 + 0x64), 4);
            func_ov004_022256ec(self, 0);
        }
    }
    return 1;
}
