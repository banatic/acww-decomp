/* title_logo: 11 functions, module ov147
 * mwccarm 1.2/base -O4,s
 * func_ov147_02299248 @ 0x02299248, 0xd8 bytes, Thumb
 * func_ov147_02299168 @ 0x02299168, 0xe0 bytes, Thumb
 * func_ov147_02299154 @ 0x02299154, 0x12 bytes, Thumb
 * func_ov147_02299134 @ 0x02299134, 0x1e bytes, Thumb
 * func_ov147_02299118 @ 0x02299118, 0x1c bytes, Thumb
 * func_ov147_022990dc @ 0x022990dc, 0x3c bytes, Thumb
 * func_ov147_02299018 @ 0x02299018, 0xc4 bytes, Thumb
 * func_ov147_02299008 @ 0x02299008, 0x10 bytes, Thumb
 * func_ov147_02298f88 @ 0x02298f88, 0x80 bytes, Thumb
 * func_ov147_02298f54 @ 0x02298f54, 0x34 bytes, Thumb
 * func_ov147_02298f20 @ 0x02298f20, 0x34 bytes, Thumb
 */

typedef struct {
    char pad_00[0xA4];
    int unk_A4;
    short unk_A8;
    unsigned char unk_AA;
} UnkStruct_022990dc;

typedef struct {
    char b[0x20];
} UnkStruct_02299018;

typedef struct {
    char pad_00[0xa4];
    int unk_A4;
    char pad_A8[0x28];
    char unk_D0;
} Object;

typedef struct {
    char pad_00[0xa4];
    int unk_A4;
    char pad_A8[0xd0 - 0xa8];
    char unk_D0;
} UnkStruct_02298f88;

typedef struct {
    char data[32];
} UnkStruct_02298f88_2;

extern void func_0203de6c(int);
extern void func_020028bc(int, int, int, int);
extern void func_020029e8(int, int);
extern int func_02002d14(void *, void *, int, int, int, int);
extern int func_02064af4(void *, void *, int);
extern int func_02002b40(void *, int, int, int);
extern void __arm MI_CpuFill8(void *, int, int);
extern int func_02002a88(void *, int, int, int, int);
extern unsigned char data_ov147_0229ab5c[];
extern unsigned char data_ov147_0229ab70[];
extern unsigned char data_ov147_0229b2ac[];
extern unsigned char data_ov147_0229ab84[];
extern unsigned char data_ov147_0229baac[];
extern unsigned char data_ov147_0229f2ac[];
extern unsigned char data_ov147_0229ab98[];
extern unsigned char data_ov147_0229ae0c[];
extern unsigned char data_ov147_0229abb0[];
extern unsigned char data_ov147_0229b0cc[];
extern unsigned char data_ov147_0229abc8[];
extern unsigned char data_ov147_0229aeec[];
extern void *data_021fbe94;
extern unsigned char data_021c75b8;
extern void func_ov147_0229a630(int *p0, int p1);
extern void func_0200277c(int);
extern void func_0203de68(int);
extern void func_02002708(int arg);
extern int func_020b9c10(void *dst, void *src, int a, int b, int c, int d);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);

void func_ov147_02299118(int arg0);
void func_ov147_022990dc(UnkStruct_022990dc *self);
int func_ov147_02299018(Object *self);
void func_ov147_02299008(void *param);
int func_ov147_02298f88(UnkStruct_02298f88 *self);
void func_ov147_02298f54(int unused, unsigned int *src, int idx);
void func_ov147_02298f20(int a, int b, int c, int d);

void func_ov147_02299248(void *receiver)
{
    func_0203de6c(1);
    func_020028bc(5, 0, 0, 0);
    func_020029e8(5, 1);
    func_02002d14(data_ov147_0229ab5c, data_021fbe94, 5, 8, 8, 15);
    func_02064af4(data_ov147_0229ab70, data_ov147_0229b2ac, 0x800);
    func_02002b40(data_ov147_0229b2ac, 5, 0x800, 0);
    func_02064af4(data_ov147_0229ab84, data_ov147_0229baac, 0x3800);
    MI_CpuFill8(data_ov147_0229f2ac, 0, 0x3800);
    func_02064af4(data_ov147_0229ab98, data_ov147_0229ae0c, 0xe0);
    func_02064af4(data_ov147_0229abb0, data_ov147_0229b0cc, 0x1e0);
    func_02064af4(data_ov147_0229abc8, data_ov147_0229aeec, 0x1e0);
    func_02002a88(data_ov147_0229f2ac, 5, 0x140, 0x140, 0x2ff);
}

void func_ov147_02299168(unsigned char *self)
{
    switch (*(unsigned char *) (self + 0xaa)) {
        case 0: {
            unsigned int flag = (data_021c75b8 == 2) ? 1 : 0;
            if (flag == 0) {
                break;
            }
            func_ov147_02299248(self);
            func_ov147_022990dc((UnkStruct_022990dc *) self);
            break;
        }
        case 6: {
            unsigned int flag = (data_021c75b8 == 2) ? 1 : 0;
            if (flag == 0) {
                break;
            }
            func_ov147_0229a630((int *) (self + 0xb0), 1);
            *(unsigned short *) (self + 0xac) = 0xe10;
            *(unsigned char *) (self + 0xaa) = 5;
            break;
        }
        case 1: {
            if (func_ov147_02299018((Object *) self) == 0) {
                break;
            }
            *(unsigned char *) (self + 0xaa) = 2;
            if (*(unsigned char *) (self + 0xab) == 0) {
                func_ov147_0229a630((int *) (self + 0xb0), 0);
            }
            break;
        }
        case 2: {
            if (*(unsigned short *) (self + 0xa8) != 0) {
                (*(unsigned short *) (self + 0xa8))--;
            } else {
                func_ov147_02299008(self);
                func_ov147_0229a630((int *) (self + 0xb0), 1);
            }
            break;
        }
        case 3: {
            if (func_ov147_02298f88((UnkStruct_02298f88 *) self) != 0) {
                *(unsigned char *) (self + 0xaa) = 4;
            }
            break;
        }
        case 4:
            break;
        case 5:
            break;
        default:
            break;
    }
}

void func_ov147_02299154(unsigned char *r0)
{
    unsigned char r1;
    r1 = *(unsigned char *) (r0 + 0xaa);
    if (r1 == 1) {
        *(unsigned int *) (r0 + 0xa4) = 0x64;
    }
}

void func_ov147_02299134(void *ptr)
{
    if (((unsigned char *) ptr)[0xaa] == 2) {
        func_ov147_02299008(ptr);
    } else {
        func_ov147_02299118((int) ptr);
    }
}

void func_ov147_02299118(int arg0)
{
    func_0200277c(5);
    func_0203de68(1);
    *(unsigned char *) (arg0 + 0xaa) = 5;
}

void func_ov147_022990dc(UnkStruct_022990dc *self)
{
    self->unk_AA = 1;
    self->unk_A4 = 0;
    self->unk_A8 = 0x4B0;
    MI_CpuFill8((void *) data_ov147_0229f2ac, 0, 0x3800);
    func_02002708(5);
}

int func_ov147_02299018(Object *self)
{
    int i;
    int x;
    int y;
    UnkStruct_02299018 *e;
    int yy;
    y = self->unk_A4;
    if (y < 0x36) {
        y += 9;
        for (i = 0; i < 15 && y >= 9; i++, y--) {
            e = &((UnkStruct_02299018 *) data_ov147_0229b0cc)[i];
            yy = y;
            x = 0;
            if (yy > 0x1f) {
                x = yy - 0x1f;
                yy = 0x1f;
            }
            for (; yy >= 0 && x < 0x18; yy--, x++) {
                if (x < 0x15) {
                    func_ov147_02298f20((int) self, (int) e, yy, x);
                }
            }
        }
        func_020b9c10(&self->unk_D0, ((char *) data_ov147_0229f2ac), 5, 0x140, 0x140, 0x2ff);
        self->unk_A4 = self->unk_A4 + 1;
    } else {
        MI_CpuCopy8(((char *) data_ov147_0229baac), ((char *) data_ov147_0229f2ac), 0x3800);
        func_020b9c10(&self->unk_D0, ((char *) data_ov147_0229f2ac), 5, 0x140, 0x140, 0x2ff);
        return 1;
    }
    return 0;
}

void func_ov147_02299008(void *param)
{
    *(int *) ((char *) param + 0xa4) = 7;
    *(char *) ((char *) param + 0xaa) = 3;
}

int func_ov147_02298f88(UnkStruct_02298f88 *self)
{
    if (self->unk_A4 == 0) {
        func_0200277c(5);
        func_0203de68(1);
        return 1;
    } else {
        int i;
        UnkStruct_02298f88_2 *p;

        self->unk_A4--;
        p = &((UnkStruct_02298f88_2 *) data_ov147_0229ae0c)[self->unk_A4];
        for (i = 0; i < 448; i++) {
            func_ov147_02298f54((int) self, (unsigned int *) p, i);
        }
        func_020b9c10(&self->unk_D0, ((char *) data_ov147_0229f2ac), 5, 0x140, 0x140, 0x2ff);
        return 0;
    }
}

void func_ov147_02298f54(int unused, unsigned int *src, int idx)
{
    unsigned int *mask = ((unsigned int *) data_ov147_0229baac) + idx * 8;
    unsigned int *dst = ((unsigned int *) data_ov147_0229f2ac) + idx * 8;
    int i;

    for (i = 0; i < 8; i++) {
        *dst++ = *mask & *src;
        src++;
        mask++;
    }
}

void func_ov147_02298f20(int a, int b, int c, int d)
{
    int mask = ((unsigned short *) data_ov147_0229b2ac)[c + (d << 5)] & 0x3ff;
    if (mask != 0x10 && mask >= 0x140) {
        func_ov147_02298f54(a, (unsigned int *) b, mask - 0x140);
    }
}
