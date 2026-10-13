/* func_ov003_02223680 @ 0x02223680, 0x10c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O1,s
 */

extern void *data_020ccf94;

struct Vec {
    int x;
    int z;
};

struct UnkStruct_02223680 {
    int unk_00;
    int unk_04;
    struct Vec pos;
    int unk_10;
    int unk_14;
};

extern void *func_0204e414(void);
extern unsigned short *func_0204f5e0(void *ctx, int cx, int cz, int dx, int dz, int layer);
extern int func_02073d90(void *p);
extern int func_0204b910(unsigned short *o);
extern int func_02044540(int id);
extern void func_02045f08(int *pos, int k);

void func_ov003_02223680(char *a, int b, struct Vec *v, int d, int e)
{
    void *ctx;
    unsigned short *o;
    struct UnkStruct_02223680 *ent;
    unsigned int id;
    int ok;
    int ok2;
    int ok4;
    int ok3;
    int x;
    int z;
    int cx;
    int cz;
    int tmp[2];

    ctx = func_0204e414();
    if (ctx == 0) {
        return;
    }
    x = v->x;
    z = v->z;
    cx = x >> 4;
    cz = z >> 4;
    o = func_0204f5e0(ctx, cx, cz, x - (cx << 4), z - (cz << 4), 0);
    if (o == 0) {
        return;
    }
    if (func_02073d90(data_020ccf94) == 0) {
        b = 0;
    }
    ent = (struct UnkStruct_02223680 *) (a + 0x1dd4) + b;
    if (ent->unk_00 != 0) {
        ok = 0;
        id = *o;
        if (id >= 0x2f && id <= 0x56) {
            ok = 1;
        }
        if (ok != 0 || !(id >= 0xc8 && id <= 0xcf)) {
            if (func_0204b910(o) != 0) {
                goto set;
            }
        }
        ok2 = 1;
        id = *o;
        if (id != 0x67 && id != 0x6b) {
            ok2 = 0;
        }
        if (ok2 != 0) {
            if (func_02044540(id) != 0) {
                goto set;
            }
        }
        ok4 = 1;
        ok3 = 0;
        id = *o;
        if (id >= 0x66 && id <= 0x68) {
            ok3 = ok4;
        }
        if (ok3 == 0 && !(id >= 0x6a && id <= 0x6c)) {
            ok4 = 0;
        }
        if (ok4 != 0) {
            goto set;
        }
        if (id >= 0x57 && id <= 0x5b) {
            goto set;
        }
        if (v->x == ent->pos.x && v->z == ent->pos.z) {
            return;
        }
        tmp[0] = v->x;
        tmp[1] = v->z;
        func_02045f08(tmp, 0);
        return;
    }
set:
    ent->unk_00 = 1;
    ent->unk_04 = b;
    {
        int pz = v->z;
        int px = v->x;
        ent->pos.x = px;
        ent->pos.z = pz;
    }
    ent->unk_10 = d;
    ent->unk_14 = e;
}
