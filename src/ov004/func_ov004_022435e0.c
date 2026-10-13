/* func_ov004_022435e0 @ 0x022435e0, 0xb4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022435e0 {
    char unk_00[0x196];
    signed char unk_196;
} UnkStruct_022435e0;

extern void func_ov004_02244f20(UnkStruct_022435e0 *self);
extern int func_ov004_02244904(UnkStruct_022435e0 *self);
extern void func_ov004_02244d58(UnkStruct_022435e0 *self);
extern void func_ov004_022449ec(UnkStruct_022435e0 *self, int a, int b, int c);
extern void func_ov004_0224497c(UnkStruct_022435e0 *self, int ang, int c, int d);
extern int func_020644cc(int a);

void func_ov004_022435e0(UnkStruct_022435e0 *self)
{
    short *h;

    h = (short *) ((char *) self + 0x98);
    func_ov004_02244f20(self);
    if (func_ov004_02244904(self) == 2) {
        *((unsigned char *) self + 0x9a) = 0;
    }
    if (*((unsigned char *) self + 0x9a) != 0) {
        func_ov004_022449ec(self, 0xaaa, 0xa, 0x46);
    } else {
        func_ov004_02244d58(self);
        func_ov004_022449ec(self, 0xaaa, 0x14, 0x50);
    }
    if (self->unk_196 == 0x33) {
        func_ov004_0224497c(self, *h, 0x19a, (func_020644cc(8) + 0x12) << 12);
        *h = (short) (*h + 0x1554);
    } else {
        func_ov004_0224497c(self, *h, 0x1200, (func_020644cc(8) + 0xa) << 12);
        *h = (short) (*h + 0xaaa);
    }
}
