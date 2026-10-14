/* func_ov004_0220c560 @ 0x0220c560, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0220fde0(void *ptr);
extern int func_02053690(int a);
extern int FX_Div(int a, unsigned int b);

void func_ov004_0220c560(void *ptr)
{
    unsigned int field;
    short tmp;
    int res;

    field = *(unsigned int *) ((char *) ptr + 0x780);
    if (field != 0x23 && field != 0x24 && field != 0x25) {
        tmp = *(short *) ((char *) ptr + 0x8e);
        tmp += 0x400;
        *(short *) ((char *) ptr + 0x8e) = tmp;
    }

    res = FX_Div(func_02053690(func_ov004_0220fde0(ptr)), 0x64000);
    res >>= 2;
    *(int *) ((char *) ptr + 0x158) = res;
    *(int *) ((char *) ptr + 0x154) = *(int *) ((char *) ptr + 0x158);
    *(int *) ((char *) ptr + 0x150) = *(int *) ((char *) ptr + 0x154);
}
