/* func_ov121_0229adac @ 0x0229adac, 0x14 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x9c];
    unsigned int flag;
} UnkStruct_0229adac;

int func_ov121_0229adac(UnkStruct_0229adac *self, int bit)
{
    return (self->flag & (1 << bit)) ? 1 : 0;
}
