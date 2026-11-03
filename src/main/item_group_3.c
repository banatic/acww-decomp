/* item_group_3: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0204be10 @ 0x0204be10, 0x28 bytes, Thumb
 * func_0204bde8 @ 0x0204bde8, 0x28 bytes, Thumb
 * func_0204bdd0 @ 0x0204bdd0, 0x18 bytes, Thumb
 */

extern int func_0204b42c(int);

int func_0204be10(unsigned short *p)
{
    int flag = (*p >= 0x1471U) && (*p <= 0x1491U);
    if (flag) {
        return 1;
    } else {
        return 0;
    }
}

int func_0204bde8(int param)
{
    int result;
    int temp;

    if (func_0204be10((unsigned short *) param) != 0) {
        temp = func_0204b42c(param);
        result = temp - 0x1471;
    } else {
        result = -1;
    }
    return result;
}

unsigned short func_0204bdd0(unsigned int arg0)
{
    if (arg0 < 0x21) {
        return (unsigned short) (arg0 + 0x1408);
    }
    return 0x1408;
}
