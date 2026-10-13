/* func_ov003_022118b8 @ 0x022118b8, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_02077898(void *self, unsigned int *out1);

typedef struct {
    unsigned char pad_00[2];
    unsigned char unk_02;
    unsigned char unk_03;
    unsigned char unk_04;
} UnkStruct_022118b8;

void func_ov003_022118b8(UnkStruct_022118b8 *self, unsigned int *out1, unsigned short *out2, unsigned char *out3)
{
    out1[0] = self->unk_02;
    out1[1] = self->unk_03;
    *out2 = func_02077898(self, out1);
    *out3 = self->unk_04;
}
