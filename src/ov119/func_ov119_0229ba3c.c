/* func_ov119_0229ba3c @ 0x0229ba3c, 0x90 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa0];
    unsigned char unk_A0;
    unsigned char pad_A1[14];
    unsigned char unk_AF;
} UnkStruct_0229ba3c;

extern int func_ov119_0229ba00(UnkStruct_0229ba3c *p);
extern int func_ov119_0229b9c8(UnkStruct_0229ba3c *p);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_ov002_0220a374(void *ptr, int a);
extern void func_ov119_0229b7c8(UnkStruct_0229ba3c *p);

void func_ov119_0229ba3c(UnkStruct_0229ba3c *p)
{
    int a, b;
    unsigned char y, z;

    if (p->unk_A0 <= 7) {
        y = p->unk_AF;
        if (y == 0) {
            p->unk_A0 = 8;
        } else if ((int) y <= (int) p->unk_A0) {
            p->unk_A0 = y - 1;
        }
    }

    a = func_ov119_0229ba00(p);
    b = func_ov119_0229b9c8(p);
    func_ov002_0220a0b4((char *) p + 0xda8, a, b);

    z = p->unk_A0;
    if (z <= 7) {
        func_ov002_0220a374((char *) p + 0xda8, 7);
    } else {
        if (z >= 14 && z <= 21) {
            func_ov002_0220a374((char *) p + 0xda8, 13);
        } else {
            func_ov002_0220a374((char *) p + 0xda8, 1);
        }
    }

    func_ov119_0229b7c8(p);
}
