/* func_ov144_0229aed4 @ 0x0229aed4, 0x54 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ee45c(void *);
extern int func_ov144_02299680(void *, int);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov144_0229ae64(void *);
extern void func_ov002_02208090(void *, int);

void func_ov144_0229aed4(void *self)
{
    int tmp;
    tmp = func_020ee45c(self);
    if (func_ov144_02299680(self, 0x20)) {
        func_ov092_02299324(tmp, 0x23, 1);
    } else {
        func_ov092_02299324(tmp, 0x44, 1);
    }
    func_ov002_02207f04(self, 0xa, 0, 0, 0x18);
    func_ov144_0229ae64(self);
    func_ov002_02208090(self, 3);
}
