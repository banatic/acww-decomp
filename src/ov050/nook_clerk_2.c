/* nook_clerk_2: 2 functions, module ov050
 * mwccarm 1.2/base -O4,s
 * func_ov050_02262df4 @ 0x02262df4, 0x40 bytes, Thumb
 * func_ov050_02262de8 @ 0x02262de8, 0xc bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x73F];
    unsigned char unk_73F;
} UnkStruct_02262df4;

extern unsigned char data_020e54a8;
extern int func_ov050_022604f8(const void *self);

// The || form shares the return 1 path.
int func_ov050_02262df4(UnkStruct_02262df4 *self)
{
    unsigned int flag;
    if (func_ov050_022604f8(self) != 0) {
        return 0;
    }
    flag = (data_020e54a8 == 1);
    if (flag == 0 || self->unk_73F == 0) {
        return 1;
    }
    return 0;
}

void func_ov050_02262de8(unsigned char *p)
{
    p[0x073f] = 1;
}
