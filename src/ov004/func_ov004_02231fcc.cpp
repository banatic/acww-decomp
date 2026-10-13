/* func_ov004_02231fcc @ 0x02231fcc, 0x88 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02231fcc {
    int a, b;
    ~UnkStruct_02231fcc() {}
};
typedef struct {
    int x, y, z;
} Vec3;
extern "C" {
extern void func_020b3220(void *);
extern void func_020b3188(void *);
extern int data_ov004_02258a30[3];
}

extern "C" void func_ov004_02231fcc(char *self, int v, char *p)
{
    UnkStruct_02231fcc t;
    if (*(signed char *) (self + 0x3520) == v) {
        char *o;
        Vec3 *w;
        int x, y, z;
        func_020b3220(p);
        o = *(char **) (p + 0xb4);
        w = (Vec3 *) (o + 0x4c);
        y = w->y;
        z = w->z;
        x = w->x;
        *(int *) (self + 0x3528) = x;
        *(int *) (self + 0x352c) = y;
        *(int *) (self + 0x3530) = z;
    } else if (*(signed char *) (self + 0x3521) == v) {
        func_020b3188(p);
    } else if (*(signed char *) (self + 0x3523) == v) {
        if (p != 0) {
            char *o = *(char **) (p + 0xb4);
            int z = *(int *) (o + 0x54);
            int x = *(int *) (o + 0x4c);
            data_ov004_02258a30[0] = x;
            data_ov004_02258a30[1] = 0x3700;
            data_ov004_02258a30[2] = z;
        }
    }
}
