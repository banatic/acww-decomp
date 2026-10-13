/* func_ov003_0221f7f0 @ 0x0221f7f0, 0x238 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off
typedef struct UnkStruct_0221f7f0 UnkStruct_0221f7f0;

struct UnkStruct_0221f7f0 {
    unsigned char pad_00[0x50];
    char *unk_50;
    unsigned char unk_54[0x148 - 0x54];
    int unk_148;
    int unk_14C;
    unsigned char unk_150[4];
};

extern int data_ov003_0223cad4;
extern void *data_021c67a4;

extern void func_020ad408(void);
extern void func_020ace24(void);
extern int *func_ov003_0221f5e8(void *p);
extern int func_0203c590(void *o);
extern void func_0203c3c4(void *o, int *a, int *b);
extern int func_0203f984(int a);
extern int func_ov003_0221f5e0(void *p);
extern int func_ov003_0221f5d8(void *p);
extern int func_ov003_0221f5ec(void *p);
extern void func_ov003_0221f120(void *p);
extern void func_ov003_0221f230(void *p);
extern void func_ov003_0221f424(void *p);

int func_ov003_0221f7f0(UnkStruct_0221f7f0 *self)
{
    int cx, cy;
    int cur;
    int lim;
    void *o;
    int found;
    int k;
    int xa, ya;
    int xb, yb;
    int xc, yc;
    int xd, yd;
    int ok;
    int tx, ty;

    data_ov003_0223cad4 = 0;
    func_020ad408();
    func_020ace24();

    cur = 0;
    cx = 0;
    cy = 0;
    lim = func_ov003_0221f5e8(&self->unk_54)[2];
    k = 0;
    o = data_021c67a4;
    if (o != 0) {
        k = func_0203c590(o);
        func_0203c3c4(o, &cx, &cy);
        cur = func_0203f984(k);
    }

    found = 0;
    for (ya = 0; ya < self->unk_14C; ya++) {
        for (xa = 0; xa < self->unk_148; xa++) {
            ty = cy;
            tx = cx;
            ok = (xa >= tx - 1 && xa <= tx + 1 && ya >= ty - 2 && ya <= ty + 1) ? 1 : 0;
            if (ok != 0) {
                if (xa == func_ov003_0221f5e0(&self->unk_54) && ya == func_ov003_0221f5d8(&self->unk_54)) {
                    found = 1;
                }
            }
        }
    }

    if (found == 0) {
        func_ov003_0221f120(&self->unk_150);
    }

    if (found == 0) {
        k = 0;
        for (yb = 0; yb < self->unk_14C; yb++) {
            for (xb = 0; xb < self->unk_148; xb++) {
                ty = cy;
                tx = cx;
                ok = (xb >= tx - 1 && xb <= tx + 1 && yb >= ty - 2 && yb <= ty + 1) ? 1 : 0;
                if (ok != 0) {
                    func_ov003_0221f230(self->unk_50 + 0xec * k);
                }
                k++;
            }
        }
        goto done;
    }

    if (func_ov003_0221f5ec(&self->unk_54) < k) {
        if (lim < cur) {
            func_ov003_0221f424(&self->unk_54);
            func_ov003_0221f120(&self->unk_150);
        } else {
            func_ov003_0221f120(&self->unk_150);
            func_ov003_0221f424(&self->unk_54);
        }
        k = 0;
        for (yc = 0; yc < self->unk_14C; yc++) {
            for (xc = 0; xc < self->unk_148; xc++) {
                ty = cy;
                tx = cx;
                ok = (xc >= tx - 1 && xc <= tx + 1 && yc >= ty - 2 && yc <= ty + 1) ? 1 : 0;
                if (ok != 0) {
                    func_ov003_0221f230(self->unk_50 + 0xec * k);
                }
                k++;
            }
        }
        goto done;
    }

    func_ov003_0221f120(&self->unk_150);
    k = 0;
    for (yd = 0; yd < self->unk_14C; yd++) {
        for (xd = 0; xd < self->unk_148; xd++) {
            ty = cy;
            tx = cx;
            ok = (xd >= tx - 1 && xd <= tx + 1 && yd >= ty - 2 && yd <= ty + 1) ? 1 : 0;
            if (ok != 0) {
                func_ov003_0221f230(self->unk_50 + 0xec * k);
            }
            k++;
        }
    }
    func_ov003_0221f424(&self->unk_54);
done:
    return 1;
}
