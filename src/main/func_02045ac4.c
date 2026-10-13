/* func_02045ac4 @ 0x02045ac4, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Vec {
    int x, y, z;
} Vec;
typedef struct Pair {
    int a, b;
} Pair;
typedef struct Entry {
    char pad_00[0x5c];
    Vec vec;
} Entry;

extern int data_020ccf94;
extern int func_02073d90(int);
extern void func_0204f794(Vec *out, int a, int b);
extern Entry *func_020961a8(int);
extern int FX_MulFunc(int, int);

int func_02045ac4(Pair *p, int skip)
{
    Vec local;
    int i;
    int res1, res2;

    if (func_02073d90(data_020ccf94) == 0) {
        return 1;
    }

    func_0204f794(&local, p->a, p->b);

    for (i = 0; i < 4; i++) {
        Entry *entry;
        Vec *sub;
        int dx, dz;

        if (i == skip) {
            continue;
        }

        entry = func_020961a8(i);
        if (entry == 0) {
            continue;
        }

        sub = &entry->vec;
        dx = local.x - sub->x;
        dz = local.z - sub->z;

        res1 = FX_MulFunc(dx, dx);
        res2 = FX_MulFunc(dz, dz);

        if (res1 + res2 >= 0x1000) {
            continue;
        }
        return 0;
    }

    return 1;
}
