/* func_020c11cc @ 0x020c11cc, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec;

typedef struct {
    char pad_00[4];
    int unk_04;
    char pad_08[0x2c];
    Vec unk_34;
    Vec unk_40;
    char pad_4C[0xc];
    int unk_58;
    char pad_5C[4];
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6C;
    int unk_70;
} UnkStruct_020c11cc;

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[8];
    int unk_68;
} UnkStruct_020c11cc_2;

extern void VEC_Add(Vec *a, Vec *b, Vec *c);
extern void *func_020961a8(int n);
extern int data_020d2308[];
extern short FX_SinCosTable_[];

void func_020c11cc(UnkStruct_020c11cc *p)
{
    Vec *q = &p->unk_34;
    UnkStruct_020c11cc_2 *obj;
    int v;
    short f;
    int t;
    int val;

    VEC_Add(q, &p->unk_40, q);
    obj = (UnkStruct_020c11cc_2 *) func_020961a8(4);
    if (obj != 0) {
        int delta = (-(obj->unk_5C - obj->unk_68) * data_020d2308[p->unk_68]) >> 12;
        int n = delta + p->unk_6C;
        p->unk_6C = n;
    }
    v = p->unk_6C;
    f = (short) ((short) p->unk_64 + p->unk_60);
    p->unk_64 = f;
    t = ((unsigned short) f >> 4) * 2;
    val = FX_SinCosTable_[t];
    val = val * p->unk_70;
    q->x = v + (val >> 12);
    if (q->y > 0x1d4000) {
        p->unk_04 = 3;
    } else if (q->x < (int) 0xfffec000) {
        q->x += 0x11e000;
    } else if (q->x > 0x114000) {
        q->x -= 0x11e000;
    }
}
