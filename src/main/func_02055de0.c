/* func_02055de0 @ 0x02055de0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_G3dRenderObjSetCallBack(char *p, int b, int c, int d, int e);

void func_02055de0(char *base, int r1, int r2, int r3, int stack0, int stack4)
{
    NNS_G3dRenderObjSetCallBack(base + 8, r1, stack4, r2, r3);
    *(int *) (base + 0x34) = stack0;
}
