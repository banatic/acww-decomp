/* func_ov004_0220f27c @ 0x0220f27c, 0x1d4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#pragma opt_propagation off
typedef struct {
    int x, y, z;
} Vec3;
typedef struct {
    int m[12];
} Mtx43;
typedef struct {
    int unk_00, unk_04, unk_08;
} UnkStruct_0220f27c;

struct UnkStruct_0220f27c_2 {
    int data[9];
};

extern Mtx43 data_021fbe48;
extern int data_ov004_02256c78;
extern UnkStruct_0220f27c data_ov004_02256e10[2];
extern UnkStruct_0220f27c data_ov004_02256e1c;
extern int data_ov004_02256e04[3];
extern int data_ov004_02256d14[3];
extern int data_ov004_02256c54;
extern UnkStruct_0220f27c data_ov004_02256c9c;
extern int data_ov004_02256c90[3];
extern void __register_global_object(UnkStruct_0220f27c *a, void *destructor, void *c);
extern void func_020012dc(void *arg0);
extern void VEC_Add(Vec3 *d, void *a, Vec3 *b);
extern void func_ov004_0220fc98(void *self, void *m, int k);
extern void MTX_MultVec43(Vec3 *v, Mtx43 *m, Vec3 *out);
extern void func_0204f818(int *a, int *b, Vec3 *v);
extern int func_ov004_0220db6c(struct UnkStruct_0220f27c_2 *l, int a, int b);

void func_ov004_0220f27c(char *self, struct UnkStruct_0220f27c_2 *l, void *m, int k)
{
    int x;
    int y;
    Vec3 p;
    Vec3 q;
    Vec3 w;
    int t;
    int i;

    p.x = *(int *) (self + 0x5c);
    p.y = *(int *) (self + 0x60);
    p.z = *(int *) (self + 0x64);
    if (m != 0) {
        VEC_Add(&p, m, &p);
    }
    if ((data_ov004_02256c78 & 1) == 0) {
        data_ov004_02256e10[0].unk_00 = 0;
        data_ov004_02256e10[0].unk_04 = 0;
        data_ov004_02256e10[0].unk_08 = 0;
        __register_global_object(&data_ov004_02256e10[0], ((void *) &func_020012dc), &data_ov004_02256e04);
        {
            UnkStruct_0220f27c *object = &data_ov004_02256e1c;
            int value = 0x2000;
            object->unk_00 = value;
            object->unk_04 = 0;
            object->unk_08 = 0;
            __register_global_object(object, ((void *) &func_020012dc), &data_ov004_02256d14);
        }
        data_ov004_02256c78 |= 1;
    }
    q.x = p.x;
    q.y = p.y;
    q.z = p.z;
    t = *(int *) (self + 0x784);
    switch (t) {
        case 0:
            if (m != 0 || k != 0) {
                func_ov004_0220fc98(self, m, k);
            } else {
                data_021fbe48 = *(Mtx43 *) (self + 0x254);
            }
            if ((data_ov004_02256c54 & 1) == 0) {
                data_ov004_02256c9c.unk_00 = 0;
                data_ov004_02256c9c.unk_04 = 0;
                data_ov004_02256c9c.unk_08 = 0;
                __register_global_object(&data_ov004_02256c9c, ((void *) &func_020012dc), &data_ov004_02256c90);
                data_ov004_02256c54 |= 1;
            }
            MTX_MultVec43((Vec3 *) &data_ov004_02256c9c, &data_021fbe48, &q);
            func_0204f818(&x, &y, &q);
            func_ov004_0220db6c(l, x, y);
            break;
        case 1:
            if (m != 0 || k != 0) {
                func_ov004_0220fc98(self, m, k);
            } else {
                data_021fbe48 = *(Mtx43 *) (self + 0x254);
            }
            i = 0;
            do {
                UnkStruct_0220f27c *element = &data_ov004_02256e10[0] + i;
                w.x = element->unk_00;
                w.y = element->unk_04;
                w.z = element->unk_08;
                MTX_MultVec43(&w, &data_021fbe48, &q);
                func_0204f818(&x, &y, &q);
                func_ov004_0220db6c(l, x, y);
                i++;
            } while (i < 2);
            break;
        default:
            q.x = p.x - 0x1000;
            q.z = p.z - 0x1000;
            func_0204f818(&x, &y, &q);
            func_ov004_0220db6c(l, x, y);
            func_ov004_0220db6c(l, x + 1, y);
            func_ov004_0220db6c(l, x, y + 1);
            func_ov004_0220db6c(l, x + 1, y + 1);
            break;
    }
}
