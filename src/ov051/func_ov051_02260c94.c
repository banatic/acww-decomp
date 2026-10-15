/* func_ov051_02260c94 @ 0x02260c94, 0x44 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a12c0(void);
extern void func_0206844c(void *a, void *b, void *c);
extern void *data_ov051_022615c0;

struct UnkStruct_02260c94 {
    unsigned char pad_00[0x40];
    void *unk_40;
};

void func_ov051_02260c94(struct UnkStruct_02260c94 *self)
{
    char buf[8];
    if (func_020a12c0()) {
        buf[0] = 0x1a;
        func_0206844c(self->unk_40, buf, data_ov051_022615c0);
    } else {
        buf[1] = 0x10;
        func_0206844c(self->unk_40, &buf[1], data_ov051_022615c0);
    }
}
