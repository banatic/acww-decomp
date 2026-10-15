/* func_ov116_0229e47c @ 0x0229e47c, 0x50 bytes, Thumb, module ov116
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov116_0229e2e0(void);
extern void func_ov116_0229e2c8(void *);
extern void func_ov116_0229e2b0(void *);
extern void func_02002708(int);
extern void func_ov116_0229dda8(void *, int);
extern void func_ov116_0229e3a8(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_ov002_02208090(void *, int);

void func_ov116_0229e47c(void *r0)
{
    void *r4 = r0;
    func_ov116_0229e2e0();
    func_ov116_0229e2c8(r4);
    func_ov116_0229e2b0(r4);
    func_ov002_02207f20(r4, 0xb, 0, 0, 0x30);
    func_02002708(3);
    func_02002708(6);
    func_ov116_0229dda8(r4, 1);
    func_ov116_0229e3a8(r4);
    func_ov002_02208090(r4, 1);
}
