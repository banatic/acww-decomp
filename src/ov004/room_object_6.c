/* room_object_6: 4 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_0220cfec @ 0x0220cfec, 0x4 bytes, Thumb
 * func_ov004_0220cfd4 @ 0x0220cfd4, 0x18 bytes, Thumb
 * func_ov004_0220cfd0 @ 0x0220cfd0, 0x4 bytes, Thumb
 * func_ov004_0220cf90 @ 0x0220cf90, 0x40 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[4];
    unsigned char unk_04;
} UnkStruct_0220cfec;

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x16c - 0x90];
    short unk_16C;
} UnkStruct_0220cf90;

extern int func_ov004_0220ebe0(UnkStruct_0220cf90 *, int);
extern int func_ov004_0220ccf8(UnkStruct_0220cf90 *, int);
extern int func_02095380(int);

void func_ov004_0220cfec(UnkStruct_0220cfec *p, unsigned char v)
{
    p->unk_04 = v;
}

int func_ov004_0220cfd4(signed char *p, int v)
{
    unsigned int i;
    for (i = 0; i < 4; i++) {
        if (v == p[i]) {
            return 1;
        }
    }
    return 0;
}

int func_ov004_0220cfd0(unsigned char *p0)
{
    return p0[4];
}

int func_ov004_0220cf90(UnkStruct_0220cf90 *p, int b)
{
    if (func_ov004_0220ebe0(p, b)) {
        p->unk_16C = p->unk_8E + b;
        func_ov004_0220ccf8(p, 2);
        func_02095380(0x4c4);
        return 1;
    }
    return 0;
}
