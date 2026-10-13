/* func_ov003_02233674 @ 0x02233674, 0xac bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022353a4(void *a, int b, int c);
extern void func_ov068_02270b00(void *a);
extern void func_ov068_02270d54(void *a);
extern void func_ov068_02270d24(void *a, int b);
extern void func_ov068_02270890(void *a);
extern void func_ov003_02234cc4(void *a);
extern void func_ov003_022348dc(void *a, int b);
extern void func_ov068_02270df8(void *a);

void func_ov003_02233674(char *self)
{
    switch (*(unsigned char *) (self + 0x251)) {
        case 0:
            func_ov003_022353a4(self, 0, 1);
            func_ov068_02270b00(self);
            break;
        case 2:
            func_ov003_022353a4(self, 0, 1);
            func_ov068_02270d54(self);
            break;
        case 3:
        case 7:
        case 8:
            func_ov068_02270d24(self + 0x210, 0);
            func_ov068_02270890(self);
            break;
        case 0xb:
            func_ov003_022353a4(self, 0, 1);
            func_ov003_02234cc4(self);
            func_ov003_022348dc(self, 0x1333);
            break;
        case 4:
            func_ov068_02270df8(self);
            break;
        case 0x13:
            break;
    }
    *(char *) (self + 0x249) = 1;
}
