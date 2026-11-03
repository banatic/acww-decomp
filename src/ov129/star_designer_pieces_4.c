/* star_designer_pieces_4: 8 functions, module ov129
 * mwccarm 1.2/base -O4,s
 * func_ov129_0229c2d8 @ 0x0229c2d8, 0x24 bytes, Thumb
 * func_ov129_0229c1f8 @ 0x0229c1f8, 0xe0 bytes, Thumb
 * func_ov129_0229c1d4 @ 0x0229c1d4, 0x24 bytes, Thumb
 * func_ov129_0229c170 @ 0x0229c170, 0x64 bytes, Thumb
 * func_ov129_0229c140 @ 0x0229c140, 0x30 bytes, Thumb
 * func_ov129_0229c118 @ 0x0229c118, 0x28 bytes, Thumb
 * func_ov129_0229c0e8 @ 0x0229c0e8, 0x30 bytes, Thumb
 * func_ov129_0229c094 @ 0x0229c094, 0x54 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0xA6];
    unsigned short unk_A6;
} UnkStruct_0229c2d8;

typedef struct {
    char pad_00[0x94];
    int unk_94;
    int unk_98;
    char pad_9C[0xa6 - 0x9c];
    u16 unk_A6;
    char pad_A8[2];
    u16 unk_AA;
    char pad_AC[0xb0 - 0xac];
    u8 unk_B0;
    u8 unk_B1;
    char pad_B2[1];
    u8 unk_B3;
    char pad_B4[0x734 - 0xb4];
    char unk_734;
    char pad_735[0x2f98 - 0x735];
    u8 tab[4];
} UnkStruct_0229c1f8;

typedef struct {
    char pad_00[0xa8];
    unsigned short unk_A8;
} UnkStruct_0229c1d4;

struct UnkStruct_0229c140 {
    char pad_00[0xb4];
    unsigned char counter;
};

typedef struct Entry {
    unsigned char pad_00[0x2a];
    unsigned short arr[16];
} Entry;

extern void func_ov129_0229bf30(void *p, unsigned short value);
extern int func_ov129_0229bd4c(UnkStruct_0229c1f8 *self, int a, int b);
extern int func_ov129_0229bbd8(UnkStruct_0229c1f8 *self, int a, int b);
extern int func_ov129_0229bca4(UnkStruct_0229c1f8 *self, int a);
extern void func_ov127_02299a00(void *p, int a, int b);
extern int func_0206fc8c(void);
extern void *func_020b1530(int idx);

void func_ov129_0229c2d8(UnkStruct_0229c2d8 *p)
{
    if (p->unk_A6 != 0xFFFF) {
        func_ov129_0229bf30(p, p->unk_A6);
        p->unk_A6 = 0xFFFF;
    }
}

void func_ov129_0229c1f8(UnkStruct_0229c1f8 *self)
{
    int idx;
    int k;

    if (func_ov129_0229bd4c(self, self->unk_94, self->unk_98) != 0) {
        if (self->unk_B0 != 0xff && self->unk_B3 != 0xff && self->unk_B0 != self->unk_B3) {
            switch (self->unk_B1) {
                case 1:
                case 2: {
                    int r = func_ov129_0229bbd8(self, self->unk_B3, self->unk_B0);
                    if (r != 0xffff && self->tab[r] == 3) {
                        self->unk_AA = (u16) r;
                    } else if (self->unk_B1 == 2) {
                        if (func_ov129_0229bca4(self, self->unk_B0) != 0) {
                            self->unk_AA = 0xffff;
                        }
                    }
                    break;
                }
            }
        }
        idx = self->unk_AA;
    } else {
        idx = 0xffff;
    }
    if (idx != self->unk_A6) {
        func_ov129_0229c2d8((UnkStruct_0229c2d8 *) self);
    }
    if (idx != 0xffff) {
        k = self->tab[idx];
        if (k == 2) {
            func_ov127_02299a00(&self->unk_734, idx, 0xb);
        } else if (k == 3) {
            func_ov127_02299a00(&self->unk_734, idx, 8);
        }
    }
    self->unk_A6 = (u16) idx;
}

void func_ov129_0229c1d4(UnkStruct_0229c1d4 *p)
{
    if (p->unk_A8 != 0xFFFF) {
        func_ov129_0229bf30(p, p->unk_A8);
        p->unk_A8 = 0xFFFF;
    }
}

void func_ov129_0229c170(char *p0)
{
    int v;
    unsigned char byte;

    p0[0xb4] = 5;
    if (*(unsigned short *) (p0 + 0xaa) != *(unsigned short *) (p0 + 0xa8)) {
        func_ov129_0229c1d4((UnkStruct_0229c1d4 *) p0);
    }

    v = *(unsigned short *) (p0 + 0xaa);
    if (v != 0xffff) {
        byte = *(unsigned char *) (p0 + v + 0x2f98);
        if ((unsigned char) (byte + 0xfe) <= 1) {
            func_ov127_02299a00(p0 + 0x734, v, 10);
        }
    }
    *(unsigned short *) (p0 + 0xa8) = *(unsigned short *) (p0 + 0xaa);
}

void func_ov129_0229c140(struct UnkStruct_0229c140 *self)
{
    if (self->counter != 0) {
        self->counter--;
        if (self->counter == 0) {
            func_ov129_0229c1d4((UnkStruct_0229c1d4 *) self);
        }
    }
}

void func_ov129_0229c118(unsigned char *p)
{
    int i = 0;
    int j = i;
    do {
        (p + i)[0x2f98] = j;
        i++;
    } while (i < 454);
}

void func_ov129_0229c0e8(unsigned char *p)
{
    int i;
    int j;
    unsigned char *q;
    q = p + 0x2f98;
    i = 0;
    j = i;
    do {
        if ((unsigned char) (*q + 0xfe) <= 1) {
            *q = j;
        }
        q++;
        i++;
    } while (i < 454);
}

void func_ov129_0229c094(void *arg)
{
    int count = func_0206fc8c();
    int i;
    for (i = 0; i < 16; i++) {
        Entry *p;
        int j;
        if (i == count) {
            continue;
        }
        p = (Entry *) func_020b1530(i);
        if (p == 0) {
            continue;
        }
        for (j = 0; j < 16; j++) {
            unsigned short h = p->arr[j];
            if (h != 0xffff) {
                *((unsigned char *) arg + 0x2f98 + h) = 1;
            }
        }
    }
}
