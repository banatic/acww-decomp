/* NNS_G3dAllocAnmObj @ 0x0204c048, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_G3dAnmObjCalcSizeRequired(int a, int b);
extern void NNS_FndAllocFromAllocator(int a, int b);

void NNS_G3dAllocAnmObj(int a, int b, int c)
{
    int temp;

    temp = NNS_G3dAnmObjCalcSizeRequired(b, c);
    NNS_FndAllocFromAllocator(a, temp);
}
