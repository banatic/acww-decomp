/* func_02055050 @ 0x02055050, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_G3dRenderObjAddAnmObj(void *arg1, unsigned int arg2);

void func_02055050(void *p)
{
    NNS_G3dRenderObjAddAnmObj((char *) p + 8, *(unsigned int *) ((char *) p + 0xB4));
}
