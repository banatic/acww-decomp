/* func_020bd938 @ 0x020bd938, 0x150 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct GWork {
    unsigned char pad_00[0x24];
    int unk_24;
    int unk_28;
} data_021f8ab0;

extern int data_020d2404[];
extern int func_020644cc(int);
extern void func_020bdc50(void *, int, int, int, int);
extern void func_020bdac8(void *);
extern void func_020e88dc(void *, int, int);

struct UnkStruct_020bd938 {
    unsigned char pad_00[0x2f00];
    int unk_2F00;
    int unk_2F04;
    int unk_2F08;
    unsigned char pad_2F0C[0x2f54 - 0x2f0c];
    int unk_2F54;
};

void func_020bd938(struct UnkStruct_020bd938 *self)
{
    int r6 = 0, a = data_021f8ab0.unk_24, b = data_021f8ab0.unk_28;
    int *p;

    if (a == b) {
        if (a == 3) {
            r6 = 2;
        } else if (a == 4) {
            r6 = 4;
        }
    } else {
        if (a > b) {
            if (b == 3) {
                r6 = 3;
            } else if (b <= 3) {
                r6 = 1;
            }
        } else {
            if (b == 3) {
                r6 = 1;
            } else if (b > 3) {
                r6 = 3;
            }
        }
    }

    if (r6 == 0) {
        self->unk_2F08 = 0;
    } else {
        p = &data_020d2404[(r6 - 1) * 2];
        if (self->unk_2F00 == 0) {
            self->unk_2F00 = p[0] + func_020644cc(p[1]);
        }
        if (b >= 3) {
            self->unk_2F08 += 2;
            if (self->unk_2F08 > 0x6400) {
                self->unk_2F08 = 0x6400;
            }
        } else {
            self->unk_2F08 -= 2;
            if (self->unk_2F08 < 0) {
                self->unk_2F08 = 0;
            }
        }
        self->unk_2F04 += (self->unk_2F08 >> 8);
        while (self->unk_2F04 >= self->unk_2F00) {
            func_020bdc50(self, 0, 0x3c, 0, 0);
            self->unk_2F04 -= self->unk_2F00;
            if (self->unk_2F04 > self->unk_2F00) {
                continue;
            }
            self->unk_2F00 = p[0] + func_020644cc(p[1]);
            if (self->unk_2F00 < 0x23) {
                self->unk_2F00 = 0x23;
            }
            self->unk_2F04 = 0;
            break;
        }
    }

    if (r6 == 4) {
        func_020bdac8(self);
    }
    func_020e88dc(&self->unk_2F54, (b == 4) ? 0x1000 : 0x800, 2);
}
