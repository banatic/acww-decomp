/* func_ov003_022325d4 @ 0x022325d4, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_02271160(void *a);
extern void func_ov068_02271358(void *a);
extern void func_ov003_022319bc(void *a, void *b);
extern void func_020550e4(void *a, int b);

void func_ov003_022325d4(char *self)
{
    switch (*(unsigned char *) (self + 0x251)) {
        case 4:
            func_ov068_02271160(self);
            break;
        case 5:
            func_ov068_02271358(self);
            break;
        case 9:
        case 0xb:
            func_ov003_022319bc(self, self + 0x242);
            break;
        case 0x13:
            func_020550e4(self + 0x50, 3);
            *(char *) (self + 0x251) = 4;
            break;
    }
}
