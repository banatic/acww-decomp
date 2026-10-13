/* func_ov003_02223d14 @ 0x02223d14, 0xb4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct M16 {
    int a[4];
};
struct Vec {
    int x, y, z;
};
struct Pair {
    int x, y;
};
struct UnkStruct_02223d14 {
    char pad_00[0x40];
    int unk_40;
};
struct Node {
    int unk_00;
};

extern "C" int func_0204cab4(void);
extern "C" struct Node *func_ov003_02223e88(struct UnkStruct_02223d14 *);
extern "C" void func_ov003_02223dc8(struct UnkStruct_02223d14 *, struct Node *, int *, int *, struct Vec *, int,
                                    struct Pair *);
extern "C" void func_ov003_022240fc(struct Node *, int, int, int, int, struct Vec *, int);
extern "C" int func_ov003_022240cc(struct Node *);
extern "C" void func_02090ac4(void *, struct Vec *, int, struct M16 *);
extern const struct M16 data_ov003_0223a188;
extern unsigned char data_ov003_02236b1c[];
extern void *data_ov003_022368ec[];

extern "C" struct Node *func_ov003_02223d14(struct UnkStruct_02223d14 *o, int b, int c, int d, struct Pair *e, int f)
{
    struct M16 m = data_ov003_0223a188;
    struct Node *n = 0;
    if (data_ov003_02236b1c[func_0204cab4()] != 0) {
        n = func_ov003_02223e88(o);
        if (n != 0) {
            int i1, i2;
            struct Pair p;
            p.x = e->x;
            p.y = e->y;
            struct Vec v;
            func_ov003_02223dc8(o, n, &i1, &i2, &v, d, &p);
            struct Vec w;
            w.x = v.x;
            w.y = v.y;
            w.z = v.z;
            func_ov003_022240fc(n, i1, 0, b, c, &w, f);
            if (func_ov003_022240cc(n)) {
                func_02090ac4(data_ov003_022368ec[i1], &v, 0, &m);
            } else {
                n->unk_00 = 3;
            }
            o->unk_40 = -1;
        }
    }
    return n;
}
