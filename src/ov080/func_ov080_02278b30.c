/* func_ov080_02278b30 @ 0x02278b30, 0x158 bytes, Thumb, module ov080
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099020(int, int);
extern int func_0209a000(void *, int);
extern void func_02098ff8(int, int);
extern void func_020154b4(void *, void *, int, int, int);
extern void func_02015de4(void *, void *, int, int);
extern void func_0206844c(void *, void *, void *);
extern unsigned char data_ov080_02279398;
extern unsigned char data_ov080_022793a8;
extern unsigned char data_ov080_022793bc;

typedef struct {
    unsigned char unk_00;
    unsigned char unk_01;
    unsigned short unk_02;
    unsigned short unk_04;
    unsigned short unk_06;
    unsigned short unk_08;
    unsigned short unk_0A;
    unsigned short unk_0C;
    unsigned short unk_0E;
    unsigned short unk_10;
    unsigned short unk_12;
    unsigned short unk_14;
} Buf;

typedef struct {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
    unsigned char pad_1F[0x40 - 0x1f];
    void *unk_40;
    unsigned char pad_44[0xb4 - 0x44];
    int unk_B4;
} UnkStruct_02278b30;

void func_ov080_02278b30(UnkStruct_02278b30 *self)
{
    Buf buf;
    int idx = 0xff;
    int r7;
    void *dataptr;

    if (self->unk_B4 >= 0) {
        if (self->unk_1E == 1 || self->unk_1E == 4) {
            self->unk_B4 = -2;
        }
        if (self->unk_1E != 2) {
            return;
        }
        buf.unk_02 = 0x1559;
        func_020154b4(self, &buf.unk_02, 0, 5, 0);
        buf.unk_04 = 0x1559;
        func_0209a000(&buf.unk_04, 0);
        buf.unk_00 = 4;
        func_0206844c(self->unk_40, &buf, &data_ov080_02279398);
    } else {
        r7 = func_020984e8();
        if (func_02099020(r7, 1) != 0) {
            dataptr = &data_ov080_022793a8;
        } else {
            dataptr = &data_ov080_022793bc;
            switch (self->unk_1E) {
                case 0:
                case 2:
                    buf.unk_06 = 0x1375;
                    if (func_0209a000(&buf.unk_06, 0) != 0) {
                        buf.unk_08 = 0x1375;
                        func_020154b4(self, &buf.unk_08, 0, 5, 0);
                        func_02098ff8(r7, 0x21);
                        buf.unk_0A = 0x1375;
                        func_02015de4(self, &buf.unk_0A, 0, 7);
                        idx = 1;
                    }
                    break;
                case 3:
                case 5:
                    buf.unk_0C = 0x1377;
                    if (func_0209a000(&buf.unk_0C, 0) != 0) {
                        buf.unk_0E = 0x1377;
                        func_020154b4(self, &buf.unk_0E, 0, 5, 0);
                        func_02098ff8(r7, 0x22);
                        buf.unk_10 = 0x1377;
                        func_02015de4(self, &buf.unk_10, 0, 7);
                        idx = 4;
                    }
                    break;
                default:
                    break;
            }
        }
        if (idx != 0xff) {
            buf.unk_01 = idx;
            func_0206844c(self->unk_40, &buf.unk_01, dataptr);
        }
    }
}
