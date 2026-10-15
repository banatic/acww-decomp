/* func_ov009_02262ef0 @ 0x02262ef0, 0x1c bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern int func_020044c0(void *self, int arg, int c, int d);

struct UnkStruct_02262ef0 {
    unsigned char pad_00[0x40];
    unsigned char flag;
};

void func_ov009_02262ef0(struct UnkStruct_02262ef0 *self, int arg)
{
    if (self->flag != 0) {
        func_020044c0(self, arg, 0x7f, 0);
    }
}
