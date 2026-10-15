/* func_ov076_02279278 @ 0x02279278, 0x58 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_020c80f8;
extern int func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);

typedef struct {
    unsigned char pad_00[0x564];
    unsigned char data[0x1b8];
    unsigned char unk_71C;
    unsigned short unk_71E;
} UnkStruct_02279278;

int func_ov076_02279278(UnkStruct_02279278 *self)
{
    if (self->unk_71C == 1) {
        self->unk_71E += 0x8000;
    }

    func_02019d0c(self->data, 3, 1, 0, 0, 0, (int) (short) self->unk_71E, 0, 0, (unsigned short) data_020c80f8, 0);

    return 1;
}
