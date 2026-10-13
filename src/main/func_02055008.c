/* func_02055008 @ 0x02055008, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_G3dRenderObjRemoveAnmObj(void *a, void *b);

void func_02055008(void *arg0)
{
    void *ptr;
    void *field;

    ptr = *(void **) ((char *) arg0 + 0xb4);
    if (ptr != 0) {
        field = (char *) arg0 + 8;
        NNS_G3dRenderObjRemoveAnmObj(field, *(void **) ((char *) arg0 + 0x20));
        *(void **) ((char *) arg0 + 0xb4) = 0;
    }
}
