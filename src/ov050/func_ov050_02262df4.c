/* func_ov050_02262df4 @ 0x02262df4, 0x40 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

// The || form shares the return 1 path.

extern unsigned char data_020e54a8;
extern int func_ov050_022604f8(const void *self);

typedef struct {
    unsigned char pad_00[0x73F];
    unsigned char unk_73F;
} UnkStruct_02262df4;

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
