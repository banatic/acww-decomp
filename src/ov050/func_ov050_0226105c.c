/* func_ov050_0226105c @ 0x0226105c, 0x1c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xd0];
    int unk_D0;
} UnkStruct_0226105c;

extern void func_ov050_022618d0(UnkStruct_0226105c *self, int a, int b);

void func_ov050_0226105c(UnkStruct_0226105c *self, int value)
{
    if (value != 4) {
        func_ov050_022618d0(self, 2, value);
        self->unk_D0 = 0x48;
    }
}
