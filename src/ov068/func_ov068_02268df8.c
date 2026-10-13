/* func_ov068_02268df8 @ 0x02268df8, 0x148 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec;

typedef struct {
    char pad_00[0x5c];
    Vec pos;
    Vec pos2;
    char pad_74[0x8e - 0x74];
    short unk_8E;
    char pad_90[4];
    short unk_94;
    char pad_96[0x350 - 0x96];
    char unk_350[0x564 - 0x350];
    char unk_564[0x83c - 0x564];
    char unk_83C[0x898 - 0x83c];
    char unk_898[0xa0c - 0x898];
    int unk_A0C;
} UnkStruct_02268df8;

extern void *data_021c80bc;          // 0x021c80bc
extern unsigned short data_020c80f8; // 0x020c80f8
extern const int data_021fbee8[];    // 0x021fbee8
extern int data_020c814c;            // 0x020c814c

extern int func_0204f490(void *, int *, int *, int *, int *, unsigned short *, unsigned short *, int, int);
extern void func_0204f778(Vec *, int, int, int, int);
extern int func_0200322c(Vec *, Vec *);
extern void func_0201aff4(void *, int);
extern void func_02019c6c(void *, int, int);
extern void func_ov068_02266c34(void *, void *, int, int, int, const void *, int, int, int);
extern void func_02035684(int, int, int);
extern void func_020791a4(int);
extern void func_0201cbbc(void *);
extern void func_0203e2ec(void);

int func_ov068_02268df8(void *self, UnkStruct_02268df8 *obj)
{
    unsigned short ids[2];
    int a, b, c, d;
    Vec v1;
    Vec v2;
    void *g;
    Vec *dp;
    Vec *dp2;

    g = data_021c80bc;
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    if (g == 0) {
        goto tail;
    }
    ids[0] = 0x5014;
    ids[1] = 0x501a;
    if (func_0204f490(g, &a, &b, &c, &d, &ids[0], &ids[1], 1, 0) == 0) {
        goto tail;
    }
    v2.x = 0;
    v2.y = 0;
    v2.z = 0;
    func_0204f778(&v2, a, b, c, d);
    v1.x = v2.x;
    v1.y = v2.y;
    v1.z = v2.z;
    v1.x = v2.x - 0x2000;
    v1.z = v2.z + 0x8000;
    v1.y = 0;
    dp = &obj->pos;
    dp->x = v1.x;
    dp->y = v1.y;
    dp->z = v1.z;
    dp2 = &obj->pos2;
    dp2->x = dp->x;
    dp2->y = dp->y;
    dp2->z = dp->z;
    obj->unk_8E = (short) func_0200322c(&v1, &v2);
    obj->unk_94 = obj->unk_8E;
    func_0201aff4(obj->unk_350, obj->unk_8E);
tail:
    obj->unk_A0C = 0;
    func_02019c6c(obj->unk_564, 1, data_020c80f8);
    func_ov068_02266c34(obj->unk_898, obj, 1, 0, 0, data_021fbee8, 4, data_020c814c, 1);
    func_02035684(0x12, 0xf, 0);
    func_020791a4(-1);
    func_0201cbbc(obj->unk_83C);
    func_0203e2ec();
    return 1;
}
