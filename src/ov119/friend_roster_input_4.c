/* friend_roster_input_4: 3 functions, module ov119
 * mwccarm 1.2/base -O4,s
 * func_ov119_0229ba3c @ 0x0229ba3c, 0x90 bytes, Thumb
 * func_ov119_0229ba00 @ 0x0229ba00, 0x3c bytes, Thumb
 * func_ov119_0229b9c8 @ 0x0229b9c8, 0x36 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xa0];
    unsigned char unk_A0;
    unsigned char pad_A1[14];
    unsigned char unk_AF;
} UnkStruct_0229ba3c;

struct UnkStruct_0229ba00 {
    char pad_00[0xA0];
    unsigned char kind;
};

extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_ov002_0220a374(void *ptr, int a);
extern void func_ov119_0229b7c8(UnkStruct_0229ba3c *p);
extern int func_ov090_022990b8(int index);

int func_ov119_0229ba00(struct UnkStruct_0229ba00 *p);
int func_ov119_0229b9c8(void *ptr);

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

    a = func_ov119_0229ba00((struct UnkStruct_0229ba00 *) p);
    b = func_ov119_0229b9c8((void *) p);
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

int func_ov119_0229ba00(struct UnkStruct_0229ba00 *p)
{
    unsigned char v = p->kind;
    if (v <= 7) {
        return 0x20;
    }
    if (v >= 14 && v <= 21) {
        return func_ov090_022990b8(v - 14);
    }
    if (v >= 8 && v <= 13) {
        return 0xD6;
    }
    if (v == 22) {
        return 0xDB;
    }
    return 0x80;
}

int func_ov119_0229b9c8(void *ptr)
{
    unsigned char v = ((unsigned char *) ptr)[0xa0];
    if (v <= 7) {
        return v * 16 + 56;
    }
    if (v >= 14 && v <= 21) {
        return 8;
    }
    if (v >= 8 && v <= 13) {
        return (v - 8) * 16 + 63;
    }
    if (v == 22) {
        return 170;
    }
    return 96;
}
