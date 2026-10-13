/* func_02034448 @ 0x02034448, 0x198 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020c9088[];
extern unsigned char data_020c9089[];
extern unsigned char data_020c908a[];
extern unsigned char data_020c908b[];
extern unsigned char data_020c908c[];
extern unsigned char data_020c908d[];
extern unsigned char data_020c908e[];
extern unsigned char data_020c908f[];
extern unsigned char data_020c9098[];
extern int func_01ffcb2c(int a, int b);

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    unsigned char unk_10;
    unsigned char unk_11;
    unsigned char unk_12;
    unsigned char unk_13;
    unsigned char unk_14;
} UnkStruct_02034448;

#define B(t, i) (((int) (i) < 0x7c) ? (int) t[(i) * 30] : 0)
#define H(i) (((int) (i) < 0x7c) ? (int) (*(short *) &data_020c9098[(i) * 30]) << 8 : 0)

void func_02034448(UnkStruct_02034448 *self, int a, int b, int flag)
{
    int v;

    if (flag == 0) {
        self->unk_14 = (unsigned char) func_01ffcb2c(a, b);
        v = self->unk_14;
        self->unk_10 = (unsigned char) B(data_020c9088, v);
        self->unk_00 = H(self->unk_10);
        self->unk_11 = (unsigned char) B(data_020c9089, v);
        self->unk_04 = H(self->unk_11);
        self->unk_12 = (unsigned char) B(data_020c908a, v);
        self->unk_08 = H(self->unk_12);
        self->unk_13 = (unsigned char) B(data_020c908b, v);
        self->unk_0C = H(self->unk_13);
    } else {
        self->unk_14 = (unsigned char) func_01ffcb2c(a, b);
        v = self->unk_14;
        self->unk_10 = (unsigned char) B(data_020c908c, v);
        self->unk_00 = H(self->unk_10);
        self->unk_11 = (unsigned char) B(data_020c908d, v);
        self->unk_04 = H(self->unk_11);
        self->unk_12 = (unsigned char) B(data_020c908e, v);
        self->unk_08 = H(self->unk_12);
        self->unk_13 = (unsigned char) B(data_020c908f, v);
        self->unk_0C = H(self->unk_13);
    }
}
