/* func_ov141_0229a5b4 @ 0x0229a5b4, 0x2c bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229a5b4 {
    unsigned char pad_00[0x1a8b];
    unsigned char cnt;
} UnkStruct_0229a5b4;

extern void func_ov141_0229a44c(UnkStruct_0229a5b4 *self);
extern void func_ov002_022080a0(UnkStruct_0229a5b4 *self, int flag);

void func_ov141_0229a5b4(UnkStruct_0229a5b4 *self)
{
    if (self->cnt != 0) {
        self->cnt = self->cnt - 1;
    } else {
        func_ov141_0229a44c(self);
        func_ov002_022080a0(self, 1);
    }
}
