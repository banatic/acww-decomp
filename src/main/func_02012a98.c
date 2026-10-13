/* func_02012a98 @ 0x02012a98, 0x134 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern int func_020644cc(int);
extern void func_0204f794(int *v, int a, int b);
extern int func_0200322c(void *obj, int *v);
extern unsigned int func_020e92e8(void *p);
extern int FX_MulFunc(int a, int b);
extern void func_0204f7e0(int *a, int *b);
extern int func_02078e98(int *v, int b);
extern void func_02013910(void *self);
extern int func_02013518(void *self, void *obj);
extern short FX_SinCosTable_[];
extern int data_021cb5a0;

struct UnkStruct_02012a98 {
    char pad_00[4];
    int unk_04;
    char pad_08[4];
    int unk_0C;
    int unk_10;
};
struct UnkStruct_02012a98_2 {
    int unk_00;
    int unk_04;
    int unk_08;
};

int func_02012a98(struct UnkStruct_02012a98 *self, struct UnkStruct_02012a98_2 *obj)
{
    unsigned short ang = 0x7fff;
    int base;
    int i;
    int dist;
    int zc;
    int z10;
    int vec[3];
    int mode;
    int delta;
    int idx;
    int t;

    mode = func_020644cc(4);
    func_0204f794(vec, self->unk_0C, self->unk_10);
    if (mode == 0) {
        base = func_0200322c(obj, vec);
        ang = 0x1000;
    } else if (mode == 1) {
        base = (short) func_020e92e8(&data_021cb5a0);
    } else {
        base = (short) func_020e92e8(&data_021cb5a0);
        ang = ang >> 1;
    }

    i = 0;
    zc = 0;
    z10 = 0;
    while (i < 10) {
        dist = (func_020644cc(5) + 3) << 13;
        delta = (short) func_020644cc(ang);
        if (func_020644cc(2) != 0) {
            delta = (short) (delta * ~z10);
        }
        idx = ((unsigned short) (short) (delta + base) >> 4) << 1;
        t = FX_MulFunc(dist, FX_SinCosTable_[idx]);
        vec[0] = obj->unk_00 + t;
        t = FX_MulFunc(dist, FX_SinCosTable_[idx + 1]);
        vec[2] = obj->unk_08 + t;
        func_0204f7e0(vec, vec);
        if (func_02078e98(vec, zc) != 0) {
            obj->unk_00 = vec[0];
            obj->unk_08 = vec[2];
            break;
        }
        if ((i & 1) != 0 && ang != 0xffff) {
            ang = (unsigned short) (ang + 0x1000);
        }
        i++;
    }

    func_02013910(self);
    if (func_02013518(self, obj) != 0) {
        self->unk_04 = 2;
        return 1;
    }
    return 0;
}
