/* func_020563dc @ 0x020563dc, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_G3dRenderObjAddAnmObj(void *a, void *b);

void func_020563dc(void *a, void *b)
{
    void *r2 = a;
    void *r0 = b;
    void *r1 = *(void **) ((char *) r2 + 0x18);
    NNS_G3dRenderObjAddAnmObj(r0, r1);
}
