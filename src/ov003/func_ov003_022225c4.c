/* func_ov003_022225c4 @ 0x022225c4, 0x104 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y;
} UnkStruct_022225c4;
typedef struct {
    unsigned short id;
} UnkStruct_022225c4_2;

typedef struct {
    char pad_00[0x18];
    int unk_18[6];
    int unk_30, unk_34, unk_38, unk_3C, unk_40, unk_44;
    char pad_48[0xa0 - 0x48];
    unsigned char a0;
    unsigned char a1;
} UnkStruct_022225c4_3;

extern void func_0204f794(void *, int, int);
extern UnkStruct_022225c4_2 *func_0204f5e0(void *, int, int, int, int, int);
extern int func_0204f294(void *, int, int);
extern int func_0204b3d0(UnkStruct_022225c4_2 *);
extern void func_02044a30(UnkStruct_022225c4_2 *, UnkStruct_022225c4 *, int, int);
extern void func_020449d4(UnkStruct_022225c4_2 *, UnkStruct_022225c4 *);
extern void func_020449ac(UnkStruct_022225c4 *);
extern void func_ov003_02224140(int, int, int, int);

void func_ov003_022225c4(UnkStruct_022225c4_3 *self, UnkStruct_022225c4 *p, void *ctx, int flag)
{
    UnkStruct_022225c4_2 *e;
    int r;
    unsigned int ok;
    unsigned short v;
    int x, y, hx, hy;
    UnkStruct_022225c4 t1, t2, t3;

    func_0204f794(self->unk_18, p->x, p->y);
    self->unk_3C = 0;
    self->unk_40 = 0x1000;
    self->unk_44 = 0;
    self->unk_30 = 0;
    self->unk_34 = 0;
    self->unk_38 = 0;

    x = p->x;
    y = p->y;
    hx = x >> 4;
    hy = y >> 4;
    e = func_0204f5e0(ctx, hx, hy, x - (hx << 4), y - (hy << 4), 0);
    if (e != 0) {
        r = func_0204f294(ctx, p->x, p->y);
        if (func_0204b3d0(e) != 0) {
            t1.x = p->x;
            t1.y = p->y;
            func_02044a30(e, &t1, 0, 0);
        } else {
            ok = 0;
            v = e->id;
            if (v >= 0x21 && v <= 0x24) {
                ok = 1;
            }
            if (ok != 0 || (v >= 0x1f && v <= 0x20)) {
                t2.x = p->x;
                t2.y = p->y;
                func_020449d4(e, &t2);
            } else if (v == 0xe2) {
                t3.x = p->x;
                t3.y = p->y;
                func_020449ac(&t3);
            } else if (r != 0 || (v >= 0xd4 && v <= 0xda) || (v >= 0xdb && v <= 0xe1)) {
                if (flag != 0) {
                    self->a0 = 0;
                    self->a1 = 1;
                }
            }
        }
        if (func_0204f294(ctx, p->x, p->y) != 0) {
            func_ov003_02224140(p->x, p->y, 0xfff1, 0);
        }
    }
}
