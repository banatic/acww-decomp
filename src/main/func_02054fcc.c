/* func_02054fcc @ 0x02054fcc, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */
extern void NNS_G3dRenderObjRemoveAnmObj(void *a, void *b);

void func_02054fcc(void *p0)
{
    void *ptr = *(void **) ((char *) p0 + 0xb4);
    if (ptr != 0) {
        if (*(void **) ((char *) p0 + 0x18) == ptr) {
            NNS_G3dRenderObjRemoveAnmObj((char *) p0 + 8, *(void **) ((char *) p0 + 0x18));
            *(void **) ((char *) p0 + 0xb4) = 0;
        } else if (*(void **) ((char *) p0 + 0x20) == ptr) {
            NNS_G3dRenderObjRemoveAnmObj((char *) p0 + 8, *(void **) ((char *) p0 + 0x20));
            *(void **) ((char *) p0 + 0xb4) = 0;
        }
    }
}
