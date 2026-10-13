/* func_ov068_02271068 @ 0x02271068, 0x7c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x232];
    short b;
    char pad_234[6];
    short a;
    char pad_23C[0x10];
    unsigned char flag;
} UnkStruct_02271068;
int func_ov068_02271068(UnkStruct_02271068 *self)
{
    short a = self->a;
    short b = self->b;
    short timer = b - 1;

    if (timer < 0) {
        return 1;
    }
    if (self->flag != 0) {
        if (a > 2730) {
            self->flag = 0;
        }
    } else if (a < -2730) {
        self->flag = 1;
    }
    if (self->flag != 0) {
        a += 546;
    } else {
        a -= 546;
    }
    self->a = a;
    self->b = timer;
    return 0;
}
