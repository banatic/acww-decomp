/* NNS_G3dAllocAnmObj @ 0x0204c048, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int NNS_G3dAnmObjCalcSizeRequired(int a, int b);
extern int NNS_FndAllocFromAllocator(int a, int b);

int NNS_G3dAllocAnmObj(int a, int b, int c)
{
    int result;
    int temp;

    temp = NNS_G3dAnmObjCalcSizeRequired(b, c);
    result = NNS_FndAllocFromAllocator(a, temp);
    return result;
}
