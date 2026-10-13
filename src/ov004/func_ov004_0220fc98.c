/* func_ov004_0220fc98 @ 0x0220fc98, 0xf4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int m[12];
} Mtx43;

extern Mtx43 data_021fbe48;
extern int func_ov004_0220d4c8(void *p);
extern int *func_ov004_0223ce84(void);
extern int func_ov004_0220d4c0(void *p);
extern char *func_ov004_0223cd58(int *a, int b);
extern Vec3 *func_ov004_0220d4bc(void *p);
extern int func_ov004_0220d4b4(void *p);
extern void func_020e9868(Mtx43 *m, int a, int b, int c);
extern void func_020e9744(Mtx43 *m, int a);
extern void VEC_Add(Vec3 *d, void *a, Vec3 *b);
extern void func_020e96c8(Mtx43 *m, int a, int b, int c);

void func_ov004_0220fc98(char *self, void *p1, int p2)
{
    Vec3 t;
    char *o;
    int px, py, pz;
    short h;

    if (func_ov004_0220d4c8(self + 0x17c) != 0) {
        o = func_ov004_0223cd58(func_ov004_0223ce84(), func_ov004_0220d4c0(self + 0x17c));
        if (p1 != 0 || p2 != 0) {
            func_ov004_0220fc98(o, p1, p2);
        } else {
            data_021fbe48 = *(Mtx43 *) (o + 0x254);
        }
        pz = func_ov004_0220d4bc(self + 0x17c)->z;
        py = func_ov004_0220d4bc(self + 0x17c)->y;
        px = func_ov004_0220d4bc(self + 0x17c)->x;
        func_020e9868(&data_021fbe48, px, py, pz);
        func_020e9744(&data_021fbe48, func_ov004_0220d4b4(self + 0x17c));
    } else {
        t.x = *(int *) (self + 0x5c);
        t.y = *(int *) (self + 0x60);
        t.z = *(int *) (self + 0x64);
        if (p1 != 0) {
            VEC_Add(&t, p1, &t);
        }
        h = (short) (*(short *) (self + 0x8e) + p2);
        func_020e96c8(&data_021fbe48, t.x, t.y, t.z);
        func_020e9744(&data_021fbe48, h);
        func_020e9868(&data_021fbe48, *(int *) (self + 0x144), *(int *) (self + 0x148), *(int *) (self + 0x14c));
    }
}
