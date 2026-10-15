/* func_ov118_0229ac44 @ 0x0229ac44, 0x5c bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

typedef struct Ov118Struct {
    unsigned char pad_00[0xA6];
    unsigned char unk_A6;
    unsigned char pad_A7[0x5D1];
    unsigned char unk_678;
} Ov118Struct;

extern void func_ov002_0220a4c8(void *receiver);
extern int func_ov118_0229b374(void *);
extern void func_ov118_0229adf0(void *, int);

void func_ov118_0229ac44(Ov118Struct *self, int val)
{
    int t = val;
    int diff;
    int product;
    int quotient;

    if (t < 0) {
        t = 0;
    } else if (t > 0x58) {
        t = 0x58;
    }

    diff = t - self->unk_A6;

    if (diff >= 4 || diff <= -4) {
        func_ov002_0220a4c8(&self->unk_678);
        self->unk_A6 = (unsigned char) t;
    }

    product = t * func_ov118_0229b374(self);
    quotient = product / 0x58;
    func_ov118_0229adf0(self, quotient);
}
