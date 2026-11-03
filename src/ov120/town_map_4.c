/* town_map_4: 3 functions, module ov120
 * mwccarm 1.2/base -O4,s
 * func_ov120_0229a870 @ 0x0229a870, 0x78 bytes, Thumb
 * func_ov120_0229a81c @ 0x0229a81c, 0x54 bytes, Thumb
 * func_ov120_0229a7cc @ 0x0229a7cc, 0x50 bytes, Thumb
 */

typedef struct UnkStruct_0229a870 {
    unsigned char pad_00[0x98];
    unsigned short unk_98;
    unsigned char pad_9A[0xab - 0x9a];
    unsigned char unk_AB;
    unsigned char pad_AC[0x6bc - 0xac];
    unsigned int unk_6BC;
} UnkStruct_0229a870;

typedef struct {
    unsigned char pad_00[0xab];
    unsigned char unk_AB;
    unsigned char pad_AC[2];
    unsigned char unk_AE;
} Struct_ov120_0229a7cc;

extern void func_ov120_0229abdc(void *, int);
extern void func_ov120_0229a6d0(void *);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov002_0220a374(void *, int);
extern int func_ov120_0229a448(void *, unsigned int);
extern int func_ov002_0220a4f8(void *);
extern int func_ov002_0220a4d4(void *);

int func_ov120_0229a81c(void *self);
int func_ov120_0229a7cc(Struct_ov120_0229a7cc *p);

void func_ov120_0229a870(UnkStruct_0229a870 *self)
{
    int a;
    int b;

    if (func_ov120_0229a448(self, 8) == 0) {
        if (self->unk_AB == 8) {
            self->unk_AB = 0;
        }
    }

    a = func_ov120_0229a81c(self);
    b = func_ov120_0229a7cc((Struct_ov120_0229a7cc *) self);
    func_ov002_0220a0b4(&self->unk_6BC, a, b);

    if (self->unk_AB >= 2 && self->unk_AB <= 7) {
        func_ov120_0229abdc(self, self->unk_98 & ~0xf);
    }

    func_ov002_0220a374(&self->unk_6BC, 1);
    func_ov120_0229a6d0(self);
}

int func_ov120_0229a81c(void *self)
{
    if (func_ov120_0229a448(self, 0x800) != 0) {
        return *((unsigned char *) self + 0xAD);
    } else {
        unsigned char b = *((unsigned char *) self + 0xAB);
        if (b >= 2 && b <= 7) {
            return 0xA0;
        }
        if (b == 0) {
            return 0xD8;
        }
        if (b == 1) {
            return 0xBC;
        }
        if (b == 8) {
            return func_ov002_0220a4f8((unsigned char *) self + 0x674);
        }
        return 0x80;
    }
}

int func_ov120_0229a7cc(Struct_ov120_0229a7cc *p)
{
    if (func_ov120_0229a448(p, 0x800)) {
        return p->unk_AE;
    } else {
        unsigned char b = p->unk_AB;
        if (b >= 2 && b <= 7) {
            return 0x58 + ((b - 2) << 4);
        } else if (b <= 1) {
            return 0x40;
        } else if (b == 8) {
            return func_ov002_0220a4d4((char *) p + 0x674);
        } else {
            return 0x60;
        }
    }
}
