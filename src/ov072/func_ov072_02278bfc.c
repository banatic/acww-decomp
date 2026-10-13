/* func_ov072_02278bfc @ 0x02278bfc, 0x158 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099e9c(unsigned short *);
extern int func_0202ea80(int, int);
extern int func_02087178(const char *);
extern int func_020871a8(const char *);
extern void func_0208718c(const char *);
extern void func_02015fb0(void *, int, int, int, int, int);
extern void func_0209a050(int);
extern int func_020644cc(int);

extern char data_021ebcd2[];
extern unsigned int data_ov072_02279874[8][2];
extern unsigned char data_ov072_02279878[8][8];

struct UnkStruct_02278bfc {
    unsigned char pad_00[0xb8];
    int state;
};

struct Out_02278bfc {
    unsigned int word;
    unsigned char byte;
};

void func_ov072_02278bfc(struct UnkStruct_02278bfc *self, struct Out_02278bfc *out)
{
    unsigned short tmp[2];
    int r7;
    int i;
    int count;

    tmp[0] = 0x1568;
    r7 = func_02099e9c(&tmp[0]);

    if (func_0202ea80(0x14, 0) == 0) {
        if (func_02087178(data_021ebcd2) != 0) {
            self->state = 2;
            func_0202ea80(0x14, 1);
        } else {
            self->state = 0;
        }
    } else {
        if (func_020871a8(data_021ebcd2) >= 5) {
            self->state = 3;
        } else if (r7 < 0) {
            if (func_020871a8(data_021ebcd2) == 0) {
                self->state = 4;
            } else {
                self->state = 5;
                count = 5 - func_020871a8(data_021ebcd2);
                if (count < 0) {
                    count = 0;
                }
                func_02015fb0(self, count, 0, 2, 0, 0);
            }
        } else {
            if (func_0202ea80(0x15, 1) != 0) {
                self->state = 6;
            } else {
                self->state = 7;
            }
            i = 1;
            while (i <= 15) {
                func_0209a050(r7);
                if (func_020871a8(data_021ebcd2) < 5) {
                    func_0208718c(data_021ebcd2);
                }
                tmp[1] = 0x1568;
                r7 = func_02099e9c(&tmp[1]);
                if (r7 < 0) {
                    break;
                }
                i++;
            }
            func_02015fb0(self, i, 1, 2, 0, 0);
        }
    }

    if (self->state >= 0 && self->state < 8) {
        out->word = data_ov072_02279874[self->state][0];
        if (self->state == 0) {
            out->byte = (unsigned char) func_020644cc(5);
        } else if (self->state == 3) {
            out->byte = (unsigned char) (func_020644cc(5) + 0xd);
        } else {
            out->byte = data_ov072_02279878[self->state][0];
        }
    }
}
