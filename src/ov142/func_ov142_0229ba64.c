/* func_ov142_0229ba64 @ 0x0229ba64, 0xa4 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb6];
    unsigned short x1;
    unsigned char pad_B8[4];
    unsigned char x2;
    unsigned char pad_BD[4];
    unsigned char x3;
    unsigned char x4;
    unsigned char pad_C3[1];
    unsigned short c4[9];
    unsigned short d6[9];
    unsigned char pad_E8[0x184e - 0xd6 - 18];
    unsigned short a3[9];
} UnkStruct_0229ba64;

extern int func_ov142_0229a0f8(UnkStruct_0229ba64 *, int, int);
extern void func_ov142_0229a9bc(UnkStruct_0229ba64 *);
extern void func_ov142_0229a988(UnkStruct_0229ba64 *);
extern void func_ov142_0229a954(UnkStruct_0229ba64 *);
extern void func_ov142_0229a91c(UnkStruct_0229ba64 *);
extern void func_ov142_0229a8e8(UnkStruct_0229ba64 *);
extern void func_ov142_0229a8b4(UnkStruct_0229ba64 *);
extern void func_ov142_0229a7e0(UnkStruct_0229ba64 *);
extern void func_ov142_0229a880(UnkStruct_0229ba64 *);
extern void func_ov142_0229a84c(UnkStruct_0229ba64 *);
extern void func_ov002_0220a580(void *);

void func_ov142_0229ba64(UnkStruct_0229ba64 *p)
{
    int i;

    for (i = 0; i < 9; i++) {
        p->c4[i] = 0;
        p->d6[i] = 0;
    }

    for (i = 0; i < 9; i++) {
        p->a3[i] = 0xfff1;
    }

    p->x1 = 0;
    p->x2 = 9;
    p->x3 = 3;
    p->x4 = 0;

    func_ov142_0229a0f8(p, 9, -1);
    func_ov142_0229a9bc(p);
    func_ov142_0229a988(p);
    func_ov142_0229a954(p);
    func_ov142_0229a91c(p);
    func_ov142_0229a8e8(p);
    func_ov142_0229a8b4(p);
    func_ov142_0229a7e0(p);
    func_ov142_0229a880(p);
    func_ov142_0229a84c(p);

    func_ov002_0220a580((char *) p + 0x14c);
}
