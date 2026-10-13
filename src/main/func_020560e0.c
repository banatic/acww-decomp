/* func_020560e0 @ 0x020560e0, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_G3dTexGetRequiredSize(int a);
extern int NNS_G3dTex4x4GetRequiredSize(int a);
extern int func_02055c74(int a, int b);
extern int func_02055c68(int a, int b);
extern int (*NNS_GfdDefaultFuncAllocTexVram)(int, int, int);
extern int func_02056140(int a, int b, int c);

int func_020560e0(int a, int b)
{
    int v6, v7, v2;
    v6 = NNS_G3dTexGetRequiredSize(a);
    v7 = NNS_G3dTex4x4GetRequiredSize(a);
    if (b) {
        v6 = func_02055c74(b, v6);
        v2 = func_02055c68(b, v7);
    } else {
        v6 = NNS_GfdDefaultFuncAllocTexVram(v6, 0, 0);
        v2 = NNS_GfdDefaultFuncAllocTexVram(v7, 1, 0);
    }
    return func_02056140(a, v6, v2);
}
