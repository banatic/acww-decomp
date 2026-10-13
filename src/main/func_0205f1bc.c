/* func_0205f1bc @ 0x0205f1bc, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205f240(void *);
extern int func_0205f2e0(void *, int);
extern int NNS_G3dGetJntAnmSet(int);
extern int func_02107b44(int, int);
extern int func_0205f130(void *, int);
extern char data_021ca16c[];
extern void func_02054cac(int, int, int, int, int, int, int);

void func_0205f1bc(int p1, int p2, int p3, int p4, unsigned char p5)
{
    int v1, v2, r6, t;
    func_0205f240(data_021ca16c);
    v1 = func_0205f2e0(data_021ca16c, p2);
    v2 = NNS_G3dGetJntAnmSet(v1);
    r6 = func_02107b44(v2, 0);
    t = func_0205f130(data_021ca16c, p2);
    func_02054cac(t, r6, p4, p5, 0x1000, 0, 0);
}
