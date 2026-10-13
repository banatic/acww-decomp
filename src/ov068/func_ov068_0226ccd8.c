/* func_ov068_0226ccd8 @ 0x0226ccd8, 0xc bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_0226cce4(void *a, void *b);

typedef struct {
    unsigned char pad_00[0x10];
    void *unk_10;
} UnkStruct_0226ccd8;

void func_ov068_0226ccd8(UnkStruct_0226ccd8 *self)
{
    func_ov068_0226cce4(self, self->unk_10);
}
