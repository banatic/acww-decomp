/* beside_spot: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02087b88 @ 0x02087b88, 0x2 bytes, Thumb
 * func_02087b84 @ 0x02087b84, 0x2 bytes, Thumb
 * func_02087b78 @ 0x02087b78, 0xc bytes, Thumb
 * func_02087b30 @ 0x02087b30, 0x46 bytes, Thumb
 * func_02087b1c @ 0x02087b1c, 0x12 bytes, Thumb
 * func_02087b10 @ 0x02087b10, 0xa bytes, Thumb
 * func_02087b04 @ 0x02087b04, 0xc bytes, Thumb
 * func_02087a78 @ 0x02087a78, 0x8c bytes, Thumb
 */

struct bitflags {
    unsigned char bit0 : 1;
};

struct byteflags {
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char f2 : 2;
    unsigned char f4 : 2;
    unsigned char : 2;
};

struct UnkStruct_02087a78 {
    int unk_00;
    int pad_04;
    int unk_08;
};

struct Vec3 {
    int y;
    int z;
    int x;
};

typedef struct {
    int unk_00;
    int unk_04;
} Pair;

extern void MI_CpuFill8(int a, int b, int c);
extern int func_020644cc(int);
extern Pair data_020d06ec[];
extern short data_020d06e4[];
extern int data_021ebcd2;
extern void func_0204f7e0(void *a, void *b);
extern int func_020871a8(void *a);
extern int func_02087178(void *a);

void func_02087b88(void *object) {}

void func_02087b84(void *object) {}

void func_02087b78(int a)
{
    MI_CpuFill8(a, 0, 1);
}

void func_02087b30(unsigned char *p)
{
    *p = (*p & ~0x0C) | (((unsigned char) func_020644cc(3) & 3) << 2);
    *p = (*p & ~0x30) | (((unsigned char) func_020644cc(4) & 3) << 4);
    *p |= 2;
}

int func_02087b1c(struct bitflags *ptr)
{
    if (ptr->bit0) {
        return 1;
    } else {
        return 0;
    }
}

void func_02087b10(unsigned char *p)
{
    p[0] = (unsigned char) (p[0] & ~1);
}

void func_02087b04(unsigned char *p)
{
    *p = (*p & ~1) | 1;
}

void func_02087a78(struct byteflags *p0, void *p1, short *out, struct UnkStruct_02087a78 *p3)
{
    struct Vec3 tmp;
    int x, y;
    Pair *e;

    if (!p0->bit1) {
        func_02087b30((unsigned char *) p0);
    }

    e = &data_020d06ec[p0->f2];
    x = p3->unk_08 + e->unk_04;
    y = p3->unk_00 + e->unk_00;

    tmp.y = y;
    tmp.z = 0;
    tmp.x = x;

    func_0204f7e0(p1, &tmp);

    if (func_020871a8(&data_021ebcd2) >= 5) {
        *out = data_020d06e4[p0->f2];
    } else {
        if (func_02087178(&data_021ebcd2) != 0) {
            *out = 0;
        } else {
            *out = (p0->f4) << 14;
        }
    }
}
