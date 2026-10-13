/* func_ov134_0229b680 @ 0x0229b680, 0x34 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

struct Context {
    char pad_00[0x9f];
    volatile unsigned char count;
    char pad_A0[0x38];
};

void *func_ov134_0229b680(struct Context *self)
{
    if (self->count >= 0x11) {
        return (char *) self + 0x798;
    }
    self->count = self->count + 1;
    return (char *) self + 0xd8 + 0x6c * (self->count - 1);
}
