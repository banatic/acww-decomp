/* func_ov003_02232a44 @ 0x02232a44, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_02271644(void *a);
extern void func_ov003_022348dc(void *a, int b);
extern void func_ov003_022349a0(void *a);

void func_ov003_02232a44(char *self)
{
    // The address is written out at both uses. Case 9/0xB comes before case 7.
    switch (*(unsigned char *) (self + 0x251)) {
        case 0:
            func_ov068_02271644(self);
            break;
        case 9:
        case 0xb:
            func_ov003_022348dc(self, 0x1ccd);
            break;
        case 7:
            func_ov003_022349a0(self);
            break;
        case 0x13:
            *(char *) (self + 0x24a) = 0;
            *(char *) (self + 0x251) = 0;
            break;
    }
}
