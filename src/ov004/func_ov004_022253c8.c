/* func_ov004_022253c8 @ 0x022253c8, 0x46 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_020157c8(void *self, int a, int b);
extern void func_02015828(void *self, int a);
extern void func_ov004_022251a4(void *self, int a);

void func_ov004_022253c8(char *self)
{
    unsigned char v = self[0x1e];

    switch (v) {
        case 0x1a:
            func_020157c8(self, 0x1f, 0);
            func_02015828(self, 2);
            func_ov004_022251a4(self, 3);
            break;
        case 0x17:
            func_020157c8(self, 9, 0);
            func_02015828(self, 2);
            func_ov004_022251a4(self, 2);
            break;
    }
}
