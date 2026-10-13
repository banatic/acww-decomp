/* func_ov003_02212afc @ 0x02212afc, 0xdc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02212bec(void *p, unsigned char a, unsigned char b, int c);
extern void func_020109a0(void *self, int a, int b, int c);
extern void func_0204f794(int *out, int a, int b);
extern void func_0200fa1c(void *out, void *self, void *a, void *b, int *acc);
extern void func_0204f7e0(void *a, void *b);
extern int func_020e8ed8(int a, int b);
extern void func_ov003_02212bf4(void *q, void *v, int d, int k);

typedef struct {
    int x, y, z;
} Vec3;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[0x8e - 0x60];
    unsigned char unk_8E;
    char pad_8F[0x98 - 0x8f];
    int unk_98;
    char pad_9C[0x6f4 - 0x9c];
    int unk_6F4;
    char pad_6F8[0x6fc - 0x6f8];
    int unk_6FC;
    char pad_700[0x7d4 - 0x700];
    int unk_7D4;
    char pad_7D8[0x8f0 - 0x7d8];
    int unk_8F0;
} UnkStruct_02212afc_2;

typedef struct {
    char pad_00[0xc];
    unsigned char b0, b1, b2;
} UnkStruct_02212afc;

void func_ov003_02212afc(UnkStruct_02212afc_2 *self, UnkStruct_02212afc *a)
{
    void *q;
    int b, c, d;
    int acc;
    Vec3 out, tmp, cp;
    unsigned char *p;
    int x, r;

    p = &a->b0;
    q = &self->unk_7D4;
    b = a->b0;
    c = p[1];
    d = p[2];
    func_ov003_02212bec(&self->unk_8F0, b, c, d);
    func_020109a0(self, 0x49, 3, 0);
    func_0204f794(&out.x, b, c);
    if (d == 0) {
        x = self->unk_98;
        acc = 0x2000;
        while (x != 0) {
            x -= 0x171;
            if (x > 0) {
                acc += x;
            } else {
                x = 0;
            }
        }
        func_0200fa1c(&tmp, self, &self->unk_5C, &self->unk_8E, &acc);
        out.x = tmp.x;
        out.y = tmp.y;
        out.z = tmp.z;
        func_0204f7e0(&out, &out);
    }
    r = func_020e8ed8(out.x - self->unk_6F4, out.z - self->unk_6FC);
    cp.x = out.x;
    cp.y = out.y;
    cp.z = out.z;
    func_ov003_02212bf4(q, &cp, r, d);
}
