/* func_ov003_022335cc @ 0x022335cc, 0xa8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_02271398(void *a);
extern void func_ov003_02231104(void *a);
extern void func_ov003_022355d4(void *a);
extern void func_ov003_02234cc4(void *a);
extern void func_ov003_022353a4(void *a, int b, int c);
extern void func_ov003_022348dc(void *a, int b);

void func_ov003_022335cc(char *self)
{
    switch (*(unsigned char *) (self + 0x251)) {
        case 0:
            func_ov068_02271398(self);
            break;
        case 6:
            func_ov003_02231104(self);
            func_ov003_022355d4(self);
            break;
        case 9:
        case 0xb:
            func_ov003_02234cc4(self);
            func_ov003_022353a4(self, 0, 1);
            func_ov003_022348dc(self, 0x1ccd);
            break;
        case 7:
            *(char *) (self + 0x251) = 0;
            if (*(unsigned char *) (self + 0x24a) != 0) {
                *(short *) (self + 0x23a) = (short) (*(short *) (self + 0x23a) + *(short *) (self + 0x240));
            }
            break;
        case 0x13:
            *(char *) (self + 0x24a) = 0;
            *(char *) (self + 0x251) = 0;
            break;
    }
}
