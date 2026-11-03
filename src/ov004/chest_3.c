/* chest_3: 2 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02217264 @ 0x02217264, 0x48 bytes, Thumb
 * func_ov004_02217230 @ 0x02217230, 0x34 bytes, Thumb
 */

extern int func_020b67d4(void);
extern int func_ov004_0220fed0(void);
extern int func_ov004_02217124(void *self, int a);
extern int data_ov004_022476a4[];

void func_ov004_02217264(void *self, int k)
{
    switch (k) {
        case 1:
            if (func_020b67d4()) {
                if (func_ov004_0220fed0()) {
                    func_ov004_02217124(self, 1);
                } else {
                    func_ov004_02217124(self, 6);
                }
            } else {
                func_ov004_02217124(self, 6);
            }
            break;
        case 8:
            func_ov004_02217124(self, 0);
            break;
    }
}

int func_ov004_02217230(unsigned char *self)
{
    unsigned int i;
    for (i = 0; i < 3; i++) {
        if (*(int *) (self + 0x780) == data_ov004_022476a4[i]) {
            return i;
        }
    }
    return -1;
}
