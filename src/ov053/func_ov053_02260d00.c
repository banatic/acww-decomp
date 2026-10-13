/* func_ov053_02260d00 @ 0x02260d00, 0xc4 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8858(void *ptr);
extern void func_ov053_02260bb0(void *ptr, int val);
extern void func_ov053_02261524(void *ptr, int val);
extern unsigned char func_ov053_02261514(void *ptr);
extern unsigned char func_ov053_0226151c(void *ptr);
extern void func_ov004_0222bf20(void *ptr1, void *ptr2);
extern void func_ov004_0222c8c8(void);
extern void func_0200442c(void *ptr, int a, int b, int c);
extern int func_02016884(void *ptr, int a, void *ptr2);
extern int func_02019de8(void *ptr);
extern void func_02019d0c(void *ptr, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern unsigned short data_020c80f8;
int func_ov053_02260d00(void *self)
{
    if (func_020e8858(((char *) self) + 0x71a) == 0) {
        func_ov053_02260bb0(((char *) self) + 0x658, 5);
        func_ov053_02261524(self, 2);
    }
    if ((*((unsigned char *) (((char *) self) + 0x71a))) == 0x55) {
        unsigned char pair[2];
        pair[1] = func_ov053_02261514(((char *) self) + 0x658);
        pair[0] = func_ov053_0226151c(((char *) self) + 0x658);
        func_ov004_0222bf20(&pair[0], &pair[1]);
        func_ov004_0222c8c8();
        func_0200442c(((char *) self) + 0x514, 0x41, 0x7f, 0);
    }
    if (func_02016884(((char *) self) + 0x334, 0xf1, ((char *) self) + 0x2a0)) {
        if (func_02019de8(((char *) self) + 0x564)) {
            func_02019d0c(((char *) self) + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
        }
    }
    return 1;
}
