/* func_0202f7f4 @ 0x0202f7f4, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern long long func_0202f838(int *ptr, int addr);
extern int FX_Sqrt(int value);
extern int FX_Div(int a, int b);

extern unsigned char data_021c30b8[];

int func_0202f7f4(int *ptr)
{
    int val;
    int abs;

    val = FX_Sqrt((int) func_0202f838(ptr, (unsigned int) data_021c30b8));
    abs = val < 0 ? -val : val;
    if (abs < 4) {
        return 0;
    }
    *ptr = FX_Div(*ptr, val);
    *(ptr + 1) = FX_Div(*(ptr + 1), val);
    return 1;
}
