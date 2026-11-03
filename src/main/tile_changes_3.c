/* tile_changes_3: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020465b0 @ 0x020465b0, 0x50 bytes, Thumb
 * func_02046518 @ 0x02046518, 0x98 bytes, Thumb
 * func_020464d4 @ 0x020464d4, 0x42 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00;
    unsigned char b1 : 2;
    unsigned char : 0;
    unsigned char : 1;
    unsigned char b2 : 1;
    unsigned char pad_03[5];
    unsigned short unk_08;
    unsigned short unk_0A;
} UnkStruct_020464d4;

extern int func_020b6660(void);
extern void func_ov003_02224140(int a, int b, int c, int d);
extern void func_ov004_02233ad4(int a, int b, int c, int d);
extern void func_02046490(void *p);

void func_020465b0(unsigned char *p)
{
    p[0] = (p[0] & ~7) | 7;
    *(unsigned short *) (p + 8) = 0xffff;
    *(unsigned short *) (p + 10) = 0xfff1;
    p[1] &= ~3;
    p[1] &= ~0x80;
    p[2] &= ~1;
    p[1] = (p[1] & ~0x1c) | 0x1c;
    p[2] &= ~2;
    ((signed char *) p)[2] = (((signed char *) p)[2] & ~0x3c) | 0x3c;
}

int func_02046518(unsigned char *p, unsigned int a1, unsigned short a2, unsigned int a3, unsigned short a4, unsigned char a5,
                  unsigned char a6, unsigned char a7, unsigned char a8, unsigned char a9, signed char a10)
{
    *p = (unsigned char) ((*p & ~0x07) | (a1 & 0x07));
    *(unsigned short *) (p + 8) = a2;
    *(unsigned short *) (p + 10) = a3;
    *(unsigned short *) (p + 12) = a4;
    *p = (unsigned char) ((*p & ~0xf8) | ((a5 & 0x1f) << 3));
    p[1] = (unsigned char) ((p[1] & ~0x03) | (a6 & 0x03));
    p[1] = (unsigned char) ((p[1] & ~0x60) | ((a7 & 0x03) << 5));
    p[1] = (unsigned char) ((p[1] & ~0x1c) | ((a8 & 0x07) << 2));
    p[2] = (unsigned char) ((p[2] & ~0x02) | ((a9 & 0x01) << 1));
    p[2] = (unsigned char) ((*((signed char *) (p + 2)) & ~0x3c) | ((a10 & 0x0f) << 2));
    {
        int flags = (p[2] & ~0x01) | 0x01;
        p[2] = (unsigned char) flags;
        return flags;
    }
}

void func_020464d4(void *p)
{
    if (func_020b6660() != 0) {
        func_ov003_02224140(((UnkStruct_020464d4 *) p)->unk_08 >> 8, ((UnkStruct_020464d4 *) p)->unk_08 & 0xff,
                            ((UnkStruct_020464d4 *) p)->unk_0A, ((UnkStruct_020464d4 *) p)->b1);
        func_02046490(p);
    } else {
        func_ov004_02233ad4(((UnkStruct_020464d4 *) p)->unk_08 >> 8, ((UnkStruct_020464d4 *) p)->unk_08 & 0xff,
                            ((UnkStruct_020464d4 *) p)->unk_0A, ((UnkStruct_020464d4 *) p)->b2);
    }
}
