/* func_ov068_02268254 @ 0x02268254, 0xc8 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164a0(void *, int);
extern int func_02019de8(void *);
extern int func_02019c20(void *, int, int, int, int, int);
extern void func_0201651c(void *, int);
extern void func_020122e4(void *, int, int);
extern void func_020121a8(void *, int);
extern int func_020912d4(int, void *, int, int);
extern void func_0202e188(void *);
extern unsigned short data_020c80f8;

struct UnkStruct_02268254 {
    unsigned char pad_00[0x1c];
    unsigned char unk_1C;
    unsigned char pad_1D[0x2c - 0x1d];
    unsigned short unk_2C;
    unsigned char pad_2E[0x30 - 0x2e];
    int unk_30;
};

void func_ov068_02268254(struct UnkStruct_02268254 *self, unsigned char *a1)
{
    int r0;
    unsigned short r6;

    r0 = func_020164a0(a1 + 0x334, 0);
    if (r0 != 0x128) {
        return;
    }

    r0 = func_02019de8(a1 + 0x564);
    if (r0 == 0) {
        return;
    }

    self->unk_30 = 0x1400;
    r6 = data_020c80f8;

    func_02019c20(a1 + 0x564, 1, 0x129, 0, r6, 0);

    *(int *) (a1 + 0x198) = self->unk_30;

    func_0201651c(a1 + 0x334, 1);

    func_020122e4(a1 + 0x9b4, r6, 0);

    func_020121a8(a1 + 0x9b4, self->unk_30);

    self->unk_2C = 0x64;

    {
        int buf[3];
        int *p = (int *) (a1 + 0x5c);
        buf[0] = *(int *) (a1 + 0x5c);
        buf[1] = p[1];
        buf[2] = p[2];
        r0 = func_020912d4(0x4c, buf, 0, 0);
    }

    *(int *) (a1 + 0xa00) = r0;
    *(unsigned char *) (a1 + 0xa04) = 1;

    func_0202e188(a1);

    self->unk_1C = 3;
}
