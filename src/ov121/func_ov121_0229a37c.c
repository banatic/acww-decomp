/* func_ov121_0229a37c @ 0x0229a37c, 0x2c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229a37c {
    char pad_00[0xB1];
    unsigned char byte;
} UnkStruct_0229a37c;

extern int func_ov121_0229af40(UnkStruct_0229a37c *self, unsigned char byte);
extern int func_ov121_02299fc8(UnkStruct_0229a37c *self);

int func_ov121_0229a37c(UnkStruct_0229a37c *self)
{
    int r4 = func_ov121_0229af40(self, self->byte);
    if (func_ov121_02299fc8(self) == -1) {
        r4 -= 11;
    }
    return r4;
}
