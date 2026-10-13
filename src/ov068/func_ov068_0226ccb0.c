/* func_ov068_0226ccb0 @ 0x0226ccb0, 0x20 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0226ccb0 {
    char pad_00[0x18];
    int unk_18;
};
extern void func_ov068_0226cce8(struct UnkStruct_0226ccb0 *, void *, int);
extern void func_ov068_0226ccd0(struct UnkStruct_0226ccb0 *);
int func_ov068_0226ccb0(struct UnkStruct_0226ccb0 *self, void *b)
{
    int r = 0;
    if (self->unk_18 < 0x18) {
        func_ov068_0226cce8(self, b, self->unk_18);
        func_ov068_0226ccd0(self);
        r = 1;
    }
    return r;
}
