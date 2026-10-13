/* func_ov100_0229e6ec @ 0x0229e6ec, 0x90 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov100_0229e208(void *p);
extern void func_ov094_0229ad20(void *p);
extern void func_ov094_0229ace4(void *p, void *q);
extern void func_ov100_0229d1d0(void *p);
extern void func_ov094_0229b2b0(void *p);
extern void func_ov094_0229b794(void *p, int n);
extern void func_ov002_02207f20(void *p, int a, int b, int c, int d);
extern void func_02002708(int n);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void func_ov002_02208090(void *p, int a);
extern void func_ov100_0229c2b0(void *p, int a);
extern int func_ov002_02207f60(void *p);

void func_ov100_0229e6ec(void *param)
{
    func_ov100_0229e208(param);
    func_ov094_0229ad20((char *) param + 0xcc);
    func_ov094_0229ace4((char *) param + 0xcc, (char *) param + 0x28dc);
    func_ov100_0229d1d0(param);
    func_ov094_0229b2b0((char *) param + 0x0b2c);
    func_ov094_0229b794((char *) param + 0x0b2c, 0xf);
    func_ov002_02207f20(param, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(param, 6, 0, 0);
    func_ov002_02208090(param, 2);
    func_ov100_0229c2b0(param, 1);
    func_ov100_0229c2b0(param, 2);
    *(int *) ((char *) param + 0x28c4) = func_ov002_02207f60(param);
}
