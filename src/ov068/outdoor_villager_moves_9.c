/* outdoor_villager_moves_9: 3 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0226983c @ 0x0226983c, 0x98 bytes, Thumb
 * func_ov068_02269814 @ 0x02269814, 0x28 bytes, Thumb
 * func_ov068_022697cc @ 0x022697cc, 0x48 bytes, Thumb
 */

typedef struct {
    char pad_00[0x1c];
    unsigned char unk_1C;
    char pad1[0xe4 - 0x1d];
    int unk_E4;
    int unk_E8;
    int unk_EC;
    int unk_F0;
} UnkStruct_0226983c;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad1[0x898 - 0x68];
} UnkStruct_0226983c_2;

struct S_ov068 {
    char pad_00[0xe4];
    int unk_E4;
};

extern void func_ov068_0226cfd4(void *p);
extern int func_02096190(int p);
extern int func_02019c20(void *p, int a, int b, int c, int d, int e);
extern void func_ov068_02266c34(void *a, void *b, int c, int d, int e, void *f, int g, int h, int i);
extern void func_0202e188(void *p);
extern unsigned short data_020c80f8;
extern int data_020c814c;
extern unsigned char data_021fbee8[];
extern int func_020ea9e4(void *, void *);
extern int func_0201c390(int, int);
extern int func_0201c2b0(int, int);
extern short data_ov068_02278264;

int func_ov068_0226983c(UnkStruct_0226983c *p0, UnkStruct_0226983c_2 *p1)
{
    int *src;
    func_ov068_0226cfd4(p1);
    p0->unk_E4 = func_02096190(4);
    src = &p1->unk_5C;
    p0->unk_E8 = src[0];
    p0->unk_EC = src[1];
    p0->unk_F0 = src[2];
    func_02019c20(((char *) p1) + 0x564, 1, 0xDF, 1, data_020c80f8, 0);
    func_ov068_02266c34(((char *) p1) + 0x898, p1, 1, 0, 0, (void *) data_021fbee8, 4, data_020c814c, 1);
    p0->unk_1C = 0;
    func_0202e188(p1);
    return 1;
}

int func_ov068_02269814(void *a, void *b)
{
    if (func_020ea9e4((char *) b + 0x5c, (char *) a + 0xe8) <= 0xc000) {
        return 1;
    } else {
        return 0;
    }
}

int func_ov068_022697cc(int a, int b, int c)
{
    int flag = 0;
    int r;
    if (func_0201c390(b, ((struct S_ov068 *) a)->unk_E4) > c) {
        goto end;
    }
    r = func_0201c2b0(b, ((struct S_ov068 *) a)->unk_E4);
    if (r < -data_ov068_02278264) {
        goto end;
    }
    if (r > data_ov068_02278264) {
        goto end;
    }
    flag = 1;
end:
    return flag;
}
