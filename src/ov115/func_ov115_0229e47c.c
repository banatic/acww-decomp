/* func_ov115_0229e47c @ 0x0229e47c, 0x50 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov115_0229e2e0(void *);
extern void func_ov115_0229e2c8(void *);
extern void func_ov115_0229e2b0(void *);
extern void func_02002708(int);
extern void func_ov115_0229dda8(void *, int);
extern void func_ov115_0229e3a8(void *);
extern void func_ov002_02208090(void *, int);
extern void func_ov002_02207f20(void *, int, int, int, int);

void func_ov115_0229e47c(void *p)
{
    int sp0;
    func_ov115_0229e2e0(p);
    func_ov115_0229e2c8(p);
    func_ov115_0229e2b0(p);
    sp0 = 0x30;
    func_ov002_02207f20(p, 0xb, 0, 0, sp0);
    func_02002708(3);
    func_02002708(6);
    func_ov115_0229dda8(p, 1);
    func_ov115_0229e3a8(p);
    func_ov002_02208090(p, 1);
}
