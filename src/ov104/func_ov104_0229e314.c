/* func_ov104_0229e314 @ 0x0229e314, 0xa4 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208008(void *self);
extern int func_ov002_02207d24(void *addr, int param);
extern void func_ov002_02207d00(void *addr);

extern int func_ov104_0229cc30(void *self, int val, int flag);
extern void func_ov104_0229d5c0(void *self);
extern void func_ov104_0229d304(void *self);
extern int func_ov104_0229d7fc(void *self, unsigned char b);
extern int func_ov104_0229d7bc(void *self, unsigned char b);
extern void func_ov104_0229d11c(void *self, unsigned char b);
extern void func_ov104_0229d0d4(void *self, unsigned char b);
extern void func_ov104_0229d528(void *self);

typedef struct UnkStruct_0229e314 {
    unsigned char pad_00[0xb7];
    unsigned char b7;
    unsigned char b8;
    unsigned char pad_B9[0x23b8 - 0xb9];
    unsigned char sub;
} UnkStruct_0229e314;

typedef struct {
    unsigned char pad_00[2];
    unsigned short flags;
} GF;
extern GF data_021fbe40;

void func_ov104_0229e314(UnkStruct_0229e314 *self)
{
    int res;
    unsigned short flags;

    res = func_ov002_02208008(self);
    if (func_ov104_0229cc30(self, res, 1)) {
        func_ov104_0229d5c0(self);
        func_ov104_0229d304(self);
        func_ov002_02207d24((char *) self + 0x23b8, 0);
    } else {
        flags = data_021fbe40.flags;
        if (flags & 1) {
            if (func_ov104_0229d7fc(self, self->b8)) {
                return;
            }
            if (func_ov104_0229d7bc(self, self->b8)) {
                func_ov104_0229d11c(self, self->b8);
            } else {
                func_ov104_0229d0d4(self, self->b8);
            }
        } else {
            if (flags & 2) {
                func_ov104_0229d11c(self, self->b7);
            } else {
                func_ov104_0229d528(self);
                func_ov002_02207d00((char *) self + 0x23b8);
            }
        }
    }
}
