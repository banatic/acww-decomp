/* func_0203990c @ 0x0203990c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8fb8(void *);

typedef struct {
    unsigned char pad_00[0xa0];
    void *unk_A0;
} UnkStruct_0203990c;

void func_0203990c(UnkStruct_0203990c *self)
{
    if (self->unk_A0 != 0) {
        func_020a8fb8(self->unk_A0);
        self->unk_A0 = 0;
    }
}
