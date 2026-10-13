/* func_ov142_0229a84c @ 0x0229a84c, 0x34 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xd4];
    unsigned short unk_D4;
    char pad_D6[0x10];
    unsigned short unk_E6;
} UnkStruct_0229a84c;

extern int func_ov142_0229a76c(void *self, char *dst, int a, int b, int c);

void func_ov142_0229a84c(UnkStruct_0229a84c *self)
{
    self->unk_E6 = 0;
    self->unk_D4 = (unsigned short) func_ov142_0229a76c(self, (char *) self + 0x17e6, 0x450c, 0x34, 8);
}
