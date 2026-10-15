/* func_02031ecc @ 0x02031ecc, 0x214 bytes, Thumb, module main
 * mwccarm 1.2/base -O3,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int a, b;
} Pair;

typedef struct UnkStruct_02031ecc UnkStruct_02031ecc;
struct UnkStruct_02031ecc {
    int unk_00;
    Vec3 unk_04;
    Vec3 unk_10;
    Vec3 unk_1C;
    short unk_28;
    short unk_2A;
    UnkStruct_02031ecc *unk_2C;
    Vec3 unk_30[4];
    Pair unk_60[4];
    Vec3 unk_80;
    Vec3 unk_8C;
    char unk_98;
};

extern UnkStruct_02031ecc *data_021c30e4;
extern int data_021c317c;

extern void func_020eaca0(Vec3 *dst, Vec3 *a, Vec3 *b);
extern int FX_MulFunc(int a, int b);
extern int func_020320e0(Vec3 *a, Vec3 *b, Vec3 *c, Vec3 *d);
extern void func_0202f8fc(Pair *p, int a, int b);
extern int *func_0203394c(int *w, Pair *a, Pair *b, Pair *c, int d, int e, int f, UnkStruct_02031ecc *g);
extern int func_0203364c(void *p, int *w);
extern void *func_020339b8(int *w);
extern int func_02033a24(void *a, Vec3 *b, Vec3 *c, Vec3 *d, int *e, int f, UnkStruct_02031ecc *g);

void func_02031ecc(int a0, Vec3 *p1, Vec3 *p2, void *p3, void *a4, int flags, int a6)
{
    UnkStruct_02031ecc *cur;
    unsigned char buf[4];
    Pair t38, t40;
    Vec3 c48, out54;
    int w60[13];
    unsigned char *bp;
    int b, a;
    int skip;
    int i, j;
    int v, t;
    Vec3 *e1;
    Vec3 *e2;

    cur = data_021c30e4;
    b = flags & 2;
    a = flags & 1;

    while (cur != 0) {
        skip = 0;
        if (a6 == 0) {
            if (cur->unk_04.y <= 0) {
                skip = 1;
            }
        } else {
            if (cur->unk_04.y > 0) {
                skip = 1;
            }
        }
        if (skip != 0) {
            goto next;
        }

        c48.x = cur->unk_80.x;
        c48.y = cur->unk_80.y;
        c48.z = cur->unk_80.z;
        func_020eaca0(&out54, &c48, p1);

        t = out54.x;
        if (t < 0) {
            t = -t;
        }
        if (t >= cur->unk_8C.x + p2->x) {
            goto next;
        }
        t = out54.z;
        if (t < 0) {
            t = -t;
        }
        if (t >= cur->unk_8C.z + p2->z) {
            goto next;
        }

        if (b != 0) {
            bp = buf;
            for (i = 0; i < cur->unk_2A; i++) {
                *bp = (unsigned char) func_020320e0(p1, p2, &cur->unk_30[i & (cur->unk_2A - 1)],
                                                    &cur->unk_30[(i + 1) & (cur->unk_2A - 1)]);
                bp++;
            }
            v = cur->unk_04.y + FX_MulFunc(cur->unk_10.z, cur->unk_1C.y);
            for (i = 0; i < cur->unk_2A; i++) {
                if (buf[i & 3] == 0) {
                    func_0202f8fc(&t38, cur->unk_30[i & (cur->unk_2A - 1)].x, cur->unk_30[i & (cur->unk_2A - 1)].z);
                    j = i + 1;
                    func_0202f8fc(&t40, cur->unk_30[j & (cur->unk_2A - 1)].x, cur->unk_30[j & (cur->unk_2A - 1)].z);
                    func_0203394c(w60, &t38, &t40, &cur->unk_60[i & (cur->unk_2A - 1)], v, 1, 1, cur);
                    func_0203364c(p3, w60);
                    func_020339b8(w60);
                }
            }
        }

        if (a != 0) {
            func_02033a24(a4, &cur->unk_30[0], &cur->unk_30[(cur->unk_2A - 1) & 1], &cur->unk_30[(cur->unk_2A - 1) & 3],
                          &data_021c317c, 1, cur);
            func_02033a24(a4, &cur->unk_30[(cur->unk_2A - 1) & 1], &cur->unk_30[(cur->unk_2A - 1) & 2],
                          &cur->unk_30[(cur->unk_2A - 1) & 3], &data_021c317c, 1, cur);
        }
    next:
        cur = cur->unk_2C;
    }
}
