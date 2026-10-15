/* func_ov004_022402f4 @ 0x022402f4, 0xd0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y;
} UnkStruct_022402f4;

typedef struct UnkStruct_022402f4_2 UnkStruct_022402f4_2;

extern int func_ov004_02244f90(void);
extern int func_ov004_02240f2c(UnkStruct_022402f4_2 *self, int a, int b, int c, int d, int e, int f);
extern UnkStruct_022402f4_2 *func_ov004_0223ee38(void);
extern void func_ov004_02241008(UnkStruct_022402f4_2 *self, UnkStruct_022402f4 *a, UnkStruct_022402f4 *b);
extern int func_020644cc(int n);

void func_ov004_022402f4(UnkStruct_022402f4_2 *self)
{
    UnkStruct_022402f4 a, b, c, d;
    UnkStruct_022402f4_2 *o;

    func_ov004_02240f2c(self, 0x50, 0x50, 0, func_ov004_02244f90(), 0, 5);
    *((unsigned char *) self + 0x170) = 0;
    o = func_ov004_0223ee38();
    if (o != 0) {
        *((unsigned char *) self + 0x21) = 1;
        *((unsigned char *) o + 0x21) = 1;
        a.x = 0x110;
        a.y = 0x10c;
        b.x = 0x14c;
        b.y = 0x148;
        func_ov004_02241008(self, &a, &b);
    } else {
        if (*((unsigned char *) self + 0x22) != 0) {
            *(int *) ((char *) self + 0x174) = (short) (0x14 * (func_020644cc(6) + 1));
        } else {
            *(int *) ((char *) self + 0x174) = (short) (0x14 * (func_020644cc(0x1e) + 5));
        }
        c.x = 0x104;
        c.y = 0xc2;
        d.x = 0x1be;
        d.y = 0x15a;
        func_ov004_02241008(self, &c, &d);
    }
}
