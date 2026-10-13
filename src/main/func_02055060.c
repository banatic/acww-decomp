/* func_02055060 @ 0x02055060, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned short func_020550b8(int a);
void func_02056fcc(void *p, unsigned short a, int b, int c, unsigned short d);
void NNS_G3dAnmObjInit(void *p, int a, void *b, int c);

void func_02055060(void *obj, int a1, int a2, int a3, unsigned short a4, unsigned short a5)
{
    if (a5 == 0) {
        a5 = func_020550b8(a2);
    }

    func_02056fcc((void *) ((char *) obj + 0x9c), a5, a2, a3, a4);
    NNS_G3dAnmObjInit(*(void **) ((char *) obj + 0xb4), a1, *(void **) ((char *) obj + 0x5c), 0);

    {
        int value = *(int *) ((char *) obj + 0xa4);
        *(int *) (*(void **) ((char *) obj + 0xb4)) = value;
    }
}
