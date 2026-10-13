/* func_ov112_0229fae8 @ 0x0229fae8, 0x88 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xb6];
    unsigned char b6;
    unsigned char b7;
    unsigned char b8;
} UnkStruct_0229fae8;
extern void func_ov112_0229fe50(UnkStruct_0229fae8 *p, int v);
extern int _s32_div_f(int, int);
void func_ov112_0229fae8(UnkStruct_0229fae8 *self)
{
    if (self->b6 == self->b7) {
        func_ov112_0229fe50(self, 0x20);
    } else if (self->b6 < self->b7) {
        self->b6 += 8;
        if (self->b6 > self->b7) {
            self->b6 = self->b7;
        }
    } else {
        if (self->b6 < 8) {
            self->b6 = self->b7;
        } else {
            self->b6 -= 8;
            if (self->b6 < self->b7) {
                self->b6 = self->b7;
            }
        }
    }
    self->b8 = (unsigned char) _s32_div_f(self->b6 << 1, 3);
}
