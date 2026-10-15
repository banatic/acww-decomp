/* func_02056084 @ 0x02056084, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int NNS_G3dPlttGetRequiredSize(void *resource);
extern int func_02055c40(int a, int b);
extern int func_020560c0(void *a, int b);
extern int (*NNS_GfdDefaultFuncAllocPlttVram)(unsigned int, int, int);

int func_02056084(void *p0, int p1)
{
    unsigned int size = NNS_G3dPlttGetRequiredSize(p0);
    int r;
    if (p1 != 0) {
        r = func_02055c40(p1, size);
    } else {
        r = NNS_GfdDefaultFuncAllocPlttVram(size, 0, 0);
    }
    return func_020560c0(p0, r);
}
