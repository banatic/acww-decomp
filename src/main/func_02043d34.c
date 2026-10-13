/* func_02043d34 @ 0x02043d34, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204482c(int a, int b);
extern unsigned short *func_02045b5c(int a);
extern int func_02043db4(int a, int *b, int c, int d, int e);

int func_02043d34(int a, int b, int c, int d)
{
    int result = -1;
    if (func_0204482c(a, 0) == 0) {
        return -1;
    }
    {
        unsigned short *p = func_02045b5c(a);
        if (p != 0) {
            unsigned short val = *p;
            int arr[2];
            arr[0] = val >> 8;
            arr[1] = val & 0xff;
            result = func_02043db4(a, arr, b, c, d);
        }
    }
    return result;
}
