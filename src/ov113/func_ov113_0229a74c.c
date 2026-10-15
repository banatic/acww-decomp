/* func_ov113_0229a74c @ 0x0229a74c, 0x48 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov113_0229a32c(void);
extern void func_ov113_0229a2c4(void *p);
extern void func_ov002_02207ee8(char *, int, int, int, int);
extern void func_02002708(int x);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void func_ov002_02208090(void *p, int a);
extern void func_ov113_02299df0(void *self);

void func_ov113_0229a74c(void *p)
{
    func_ov113_0229a32c();
    func_ov113_0229a2c4(p);
    func_ov002_02207ee8((char *) (p), 8, 6, 0, 0x30);
    func_02002708(2);
    func_ov002_02207e80(p, 2, 0, 0);
    func_ov002_02208090(p, 1);
    func_ov113_02299df0(p);
}
