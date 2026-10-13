/* func_ov068_022738e8 @ 0x022738e8, 0x1c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_0227302c(unsigned int, unsigned char, void *);

typedef struct {
    void *unk_00;
    void *unk_04;
} Ov68Self;

typedef struct {
    unsigned char pad_00[0x2c];
    unsigned int unk_2C;
} Ov68Inner;

typedef struct {
    unsigned char pad_00[1];
    unsigned char unk_01;
} Ov68Byte;

void func_ov068_022738e8(Ov68Self *self)
{
    if (((Ov68Inner *) self->unk_04)->unk_2C != 0) {
        func_ov068_0227302c(((Ov68Inner *) self->unk_04)->unk_2C, ((Ov68Byte *) self->unk_00)->unk_01, self);
    }
}
