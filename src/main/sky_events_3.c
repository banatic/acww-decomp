/* sky_events_3: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020bdac8 @ 0x020bdac8, 0x5c bytes, Thumb
 * func_020bda88 @ 0x020bda88, 0x40 bytes, Thumb
 * func_020bd938 @ 0x020bd938, 0x150 bytes, Thumb
 */

typedef struct {
    char pad_00[0x2f10];
    int unk_2F10;
} UnkStruct_020bdac8;

struct UnkStruct_020bda88 {
    char pad_00[0x2f10];
    int unk_2F10;
};

struct UnkStruct_020bd938 {
    unsigned char pad_00[0x2f00];
    int unk_2F00;
    int unk_2F04;
    int unk_2F08;
    unsigned char pad_2F0C[0x2f54 - 0x2f0c];
    int unk_2F54;
};

extern int func_020644cc(int);
extern void func_02065268(int);
extern void *func_020bdc50(void *, int, int, int, int);
extern struct GWork {
    unsigned char pad_00[0x24];
    int unk_24;
    int unk_28;
} data_021f8ab0;
extern int data_020d2404[];
extern int func_020e88dc(void *, int, int);

void func_020bdac8(UnkStruct_020bdac8 *self)
{
    if (self->unk_2F10 <= 0) {
        self->unk_2F10 = 0x32;
    }

    self->unk_2F10 = self->unk_2F10 - 1;
    if (self->unk_2F10 > 0) {
        return;
    }

    if (func_020644cc(8) == 0) {
        func_020bdc50(self, 8, 0x3b, 0, 0);
    }

    func_02065268(0);
    self->unk_2F10 = func_020644cc(0xc8) + 10;
}

void func_020bda88(struct UnkStruct_020bda88 *p)
{
    if (p->unk_2F10 <= 0) {
        p->unk_2F10 = 0x32;
    }
    p->unk_2F10 = p->unk_2F10 - 1;
    if (p->unk_2F10 > 0) {
        return;
    }
    func_02065268(0);
    p->unk_2F10 = func_020644cc(0xc8) + 0xa;
}

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
        func_020bdac8((UnkStruct_020bdac8 *) self);
    }
    func_020e88dc(&self->unk_2F54, (b == 4) ? 0x1000 : 0x800, 2);
}
