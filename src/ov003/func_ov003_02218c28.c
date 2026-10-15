/* func_ov003_02218c28 @ 0x02218c28, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct Vec {
    int x;
    int y;
    int z;
} Vec;
typedef struct Rec {
    Vec v;
    unsigned char flag;
} Rec;
typedef struct Src {
    unsigned char pad_00[0xc];
    unsigned char a;
    unsigned char b;
} Src;

typedef struct UnkStruct_02218c28 {
    unsigned char pad_00[0x5a0];
    unsigned char unk_5A0[0x7d4 - 0x5a0];
    Rec rec; // 0x7d4
    unsigned char pad_7E4[0x820 - 0x7e4];
    unsigned short unk_820;
    unsigned short unk_822;
} UnkStruct_02218c28;

extern void func_0204f794(Vec *out, int a, int b);
extern void func_020109a0(UnkStruct_02218c28 *self, int b, int c, unsigned short d);
extern int func_0200fbe0(UnkStruct_02218c28 *self);
extern void func_0205eae0(unsigned char *p, int a, int b, int c);
extern void *data_021c80bc;
extern unsigned short *func_0204f5a8(void *ctx, Vec *v, int z);

void func_ov003_02218c28(UnkStruct_02218c28 *self, Src *src, int previous)
{
    Vec t;
    Rec *r;
    unsigned char *q = &src->a;

    func_0204f794(&t, q[0], q[1]);
    r = &self->rec;
    r->v.x = t.x;
    r->v.y = t.y;
    r->v.z = t.z;
    r->flag = 0;
    func_020109a0(self, 0x14, 3, 0);
    if (func_0200fbe0(self) == 4) {
        func_0205eae0(self->unk_5A0, 0xe, 3, 0);
    }
    self->unk_822 = *func_0204f5a8(data_021c80bc, &t, 0);
    self->unk_820 = self->unk_822;
}
