/* func_ov118_0229ae0c @ 0x0229ae0c, 0x58 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

struct func_ov118_0229ae0c_obj {
    unsigned char pad_00[0x98];
    unsigned short unk_98;
    unsigned char pad_9A[0x10];
    unsigned char unk_AA;
};

extern void func_ov118_0229ade0(struct func_ov118_0229ae0c_obj *, int);

void func_ov118_0229ae0c(struct func_ov118_0229ae0c_obj *self)
{
    unsigned char b;
    int t;
    int h;
    int k;
    unsigned char b2;

    b = self->unk_AA;
    if (b == 14) {
        return;
    }

    if (b == 13) {
        func_ov118_0229ade0(self, 0);
        return;
    }

    t = (self->unk_98 + 15) >> 4;
    if (b < t) {
        func_ov118_0229ade0(self, b << 4);
    }

    h = self->unk_98 >> 4;
    b2 = self->unk_AA;
    if (b2 <= 5) {
        k = 0;
    } else {
        k = b2 - 5;
    }

    if (h < k) {
        func_ov118_0229ade0(self, k << 4);
    }
}
