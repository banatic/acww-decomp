/* func_0205f15c @ 0x0205f15c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021ca16c;
extern int func_0205f20c(int *);
extern int func_0205f2b0(int *, int);
extern int NNS_G3dGetTexSRTAnmSet(int);
extern int func_02107bbc(int, int);
extern int func_0205f110(void *, int);
extern int func_0205f130(void *, int);
extern int func_02055e00(int);
extern void func_02056440(int, int, int, int, int, int);

void func_0205f15c(void *p0, int p1, int p2, int p3)
{
    int c, d;
    func_0205f20c(&data_021ca16c);
    c = func_02107bbc(NNS_G3dGetTexSRTAnmSet(func_0205f2b0(&data_021ca16c, p1)), 0);
    d = func_0205f110(p0, p1);
    func_02056440(d, func_02055e00(func_0205f130(p0, p1)), c, p3, 0x1000, 0);
}
