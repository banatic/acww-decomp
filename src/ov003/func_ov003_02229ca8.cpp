/* func_ov003_02229ca8 @ 0x02229ca8, 0xfc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02229ca8;
struct UnkStruct_02229ca8_2;
typedef void (UnkStruct_02229ca8::*PMF)(UnkStruct_02229ca8_2 *);
extern PMF data_ov003_0225f138[];

struct Vec3 {
    int x, y, z;
};

extern int data_020c904c;
extern void *data_020ccf94;

extern "C" {

int func_ov003_0222c364(UnkStruct_02229ca8_2 *p);
Vec3 *func_ov003_0222c1f4(UnkStruct_02229ca8_2 *p);
int func_ov003_0222c1bc(UnkStruct_02229ca8_2 *p);
void func_020044d0(UnkStruct_02229ca8 *self, Vec3 *v);
int func_020044c0(UnkStruct_02229ca8 *self, int a, int b, int c);
int func_020912d4(int a, Vec3 *v, int b, int c);
int func_02073d90(void *h);
int func_02073918(void *h, UnkStruct_02229ca8_2 *p);
void func_0204ff00(UnkStruct_02229ca8_2 *p, int a, int b, int c, int d);

void func_ov003_02229ca8(UnkStruct_02229ca8 *self, UnkStruct_02229ca8_2 *p)
{
    Vec3 v;
    Vec3 w;
    if (func_ov003_0222c364(p)) {
        Vec3 *q = func_ov003_0222c1f4(p);
        v.x = q->x;
        v.y = q->y;
        v.z = q->z;
        w = v;
        func_020044d0(self, &v);
        if (func_ov003_0222c1bc(p) == 1) {
            func_020044c0(self, 0x7e0, 0x7f, 0);
        } else if (func_ov003_0222c1bc(p) == 2) {
            func_020044c0(self, 0x7e1, 0x7f, 0);
            w.y = data_020c904c;
            func_020912d4(0x15, &w, 0, 0);
        }
    } else {
        v.x = *(int *) ((char *) self + 0x54);
        v.y = *(int *) ((char *) self + 0x58);
        v.z = *(int *) ((char *) self + 0x5c);
        func_020044d0(self, &v);
    }
    if (data_ov003_0225f138[*(int *) ((char *) self + 0x40)]) {
        (self->*data_ov003_0225f138[*(int *) ((char *) self + 0x40)])(p);
    }
    {
        void *h = data_020ccf94;
        if (func_02073d90(h) && func_02073918(h, p) == 0 && *(int *) ((char *) self + 0x40) == 4) {
            func_0204ff00(p, 8, -1, 0, 0);
        }
    }
}
}
