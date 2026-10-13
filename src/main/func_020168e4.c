/* func_020168e4 @ 0x020168e4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02082fec(int, int);
extern void func_0205cc1c(void *, int, int, int);
extern int func_0205cb94(void *);
extern int NNS_G3dGetJntAnmSet(int);
extern int func_02107b44(int, int);

int func_020168e4(int p1, int p2, int p3)
{
    void *p;
    int result;
    p = func_02082fec(p1, p3);
    result = 0;
    if (p != 0) {
        func_0205cc1c(p, p2, result, result);
        result = func_02107b44(NNS_G3dGetJntAnmSet(func_0205cb94(p)), 0);
    }
    return result;
}
