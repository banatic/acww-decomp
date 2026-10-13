/* func_ov112_0229fb8c @ 0x0229fb8c, 0x34 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb6];
    unsigned char b6;
    unsigned char b7;
    unsigned char b8;
} UnkStruct_0229fb8c;

extern void func_ov112_0229fe60(UnkStruct_0229fb8c *self, int);
extern int _s32_div_f(int, int);

void func_ov112_0229fb8c(UnkStruct_0229fb8c *self, unsigned char param)
{
    self->b6 = param;
    self->b7 = self->b6;
    func_ov112_0229fe60(self, 0x20);
    self->b8 = _s32_div_f(self->b6 * 2, 3);
}
