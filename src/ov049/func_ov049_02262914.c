/* func_ov049_02262914 @ 0x02262914, 0xd0 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int x, y, z;
} Vec3;

extern void *func_02095794(int param);
extern void func_0201b458(Vec3 *out, char *self, Vec3 *in);
extern int func_0201c378(char *self, int param);
extern int func_0201c2c8(char *self, int param);
extern int func_020e8b4c(short s, int a);
extern int data_021c80bc;
extern void func_0204ed30(int value, char *ptr);
extern int func_020eaa2c(Vec3 *out, char *ptr);
extern void func_ov049_02262a94(char *self, int param);
extern int func_ov049_0226048c(char *self);
extern int func_ov049_02260500(char *self);
extern int func_020e8840(char *ptr);

int func_ov049_02262914(char *self)
{
    Vec3 vec;
    Vec3 out;
    int r6, r1tmp, r4;
    unsigned int *pt;
    short s;

    pt = (unsigned int *) func_02095794(4);
    vec.x = pt[0];
    vec.y = pt[1];
    vec.z = pt[2];

    func_0201b458(&out, self, &vec);

    r6 = func_0201c378(self, 4);
    r1tmp = func_0201c2c8(self, 4);
    s = *(short *) (self + 0x8e);
    r4 = func_020e8b4c(s, r1tmp);

    func_0204ed30(data_021c80bc, self + 0x5c);

    if (r6 > 0x5000) {
        if (func_020eaa2c(&out, self + 0x5c) != 0) {
            func_ov049_02262a94(self, 3);
            goto later;
        }
    }
    if (r4 > 0x2000) {
        func_ov049_02262a94(self, 2);
    }
later:
    if (func_ov049_0226048c(self) != 0) {
        return 1;
    }
    if (func_ov049_02260500(self) != 0) {
        return 1;
    }
    if (*(unsigned char *) (self + 0x975) != 0) {
        if (func_020e8840(self + 0x970) == 0) {
            func_ov049_02262a94(self, 7);
        }
    }
    return 1;
}
