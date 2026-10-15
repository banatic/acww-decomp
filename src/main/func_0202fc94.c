/* func_0202fc94 @ 0x0202fc94, 0xe2 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec;

struct UnkStruct_0202fc94 {
    int unk_00;
    Vec unk_04;
    Vec unk_10;
    Vec unk_1C;
    Vec unk_28;
};

struct Seg {
    unsigned char b[0x24];
};

extern int func_0202fb28(struct UnkStruct_0202fc94 *, void *);
extern int func_0203005c(struct Seg *, Vec *, Vec *);
extern int func_0202ffbc(struct Seg *, Vec *, void *);
extern int func_0202ff14(struct Seg *, void *);
extern void func_020eaca0(Vec *, void *, Vec *);
extern int func_020ea838(Vec *);
extern void func_020eabc8(Vec *, int);
extern void VEC_Add(void *, Vec *, void *);
extern void func_02030058(struct Seg *);

int func_0202fc94(struct UnkStruct_0202fc94 *a, void *b, void *c, int d)
{
    int res;
    int n;
    Vec w;
    Vec v;
    struct Seg arr[3];
    struct Seg *s;
    Vec *pv;
    int n0;

    n0 = func_0202fb28(a, c);
    if (n0 < 0) {
        return 0;
    }
    n0 = func_0202fb28(a, b);
    if (n0 < 0) {
        return 0;
    }
    res = 0;
    if (n0 < d) {
        func_0203005c(&arr[0], &a->unk_04, &a->unk_10);
        func_0203005c(&arr[1], &a->unk_10, &a->unk_1C);
        func_0203005c(&arr[2], &a->unk_1C, &a->unk_04);
        for (s = &arr[0]; s < &arr[3]; s++) {
            n = func_0202ffbc(s, &w, b);
            if (n >= d) {
                continue;
            }
            if (func_0202ff14(s, b) == 0) {
                continue;
            }
            func_020eaca0(&v, b, &w);
            if (func_020ea838(&v) == 0) {
                pv = &a->unk_28;
                v.x = pv->x;
                v.y = pv->y;
                v.z = pv->z;
                func_020eabc8(&v, d);
            } else {
                func_020eabc8(&v, d - n);
            }
            VEC_Add(b, &v, b);
            res = 1;
            break;
        }
        func_02030058(&arr[2]);
        func_02030058(&arr[1]);
        func_02030058(&arr[0]);
    }
    return res;
}
