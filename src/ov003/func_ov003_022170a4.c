/* func_ov003_022170a4 @ 0x022170a4, 0x108 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    int a;
    int b;
    unsigned char c;
} UnkStruct_022170a4;

typedef struct {
    char pad_00[0xc];
    UnkStruct_022170a4 sub;
} Input;

extern void func_ov003_022171c4(void *p, int a, int b, unsigned char c);
extern void func_020109a0(void *p, int a, int b, int c);
extern void func_0200fa6c(Vec3 *dst, void *src);
extern int func_020310d0(Vec3 *a, void *b, int c);
extern void func_0200fa8c(Vec3 *dst, void *src);
extern int func_020e8ed8(int a, int b);
extern void func_ov003_022171dc(void *p, Vec3 *v, int angle);
extern int func_02073908(int a, int b);
extern void func_0200f268(void *p, int a);
extern int func_0200fc90(void *p);
extern int func_020644cc(int a);
extern void func_0200f27c(void *p, int a);
extern int data_020ccf94;

void func_ov003_022170a4(void *self, Input *arg)
{
    void *dest;
    int temp;
    volatile Vec3 v;
    Vec3 bufA;
    Vec3 bufB;
    Vec3 bufC;
    Vec3 out;
    UnkStruct_022170a4 *subp;
    int a, b;
    unsigned char c;
    int comp;
    int angle;

    subp = &arg->sub;
    dest = (char *) self + 0x7d4;
    a = arg->sub.a;
    b = subp->b;
    c = subp->c;

    func_ov003_022171c4((char *) self + 0x8f0, a, b, c);
    func_020109a0(self, 0x42, 3, 0);

    if (c != 0) {
        v.x = a;
        v.z = b;
    } else {
        func_0200fa6c(&bufA, self);
        comp = (func_020310d0(&bufA, &temp, 0x19) >= 0x1000) ? 1 : 0;
        if (comp != 0) {
            func_0200fa8c(&bufB, self);
            v.x = bufB.x;
            v.y = bufB.y;
            v.z = bufB.z;
        } else {
            func_0200fa6c(&bufC, self);
            v.x = bufC.x;
            v.y = bufC.y;
            v.z = bufC.z;
        }
    }

    angle = func_020e8ed8(v.x - *(int *) ((char *) self + 0x6f4), v.z - *(int *) ((char *) self + 0x6fc));

    out.x = v.x;
    out.y = v.y;
    out.z = v.z;
    func_ov003_022171dc(dest, &out, angle);

    if (func_02073908(data_020ccf94, *(int *) ((char *) self + 0x800)) != 0) {
        func_0200f268(self, 0x14);
        if (func_0200fc90(self) != 0xb) {
            if (func_020644cc(8) == 0) {
                func_0200f27c(self, 0x14);
            }
        }
    }
}
