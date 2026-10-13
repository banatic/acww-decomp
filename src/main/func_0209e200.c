/* func_0209e200 @ 0x0209e200, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e234(unsigned char *ptr, int value);

void func_0209e200(unsigned char *ptr, int add)
{
    int sum = *ptr + add;
    if (sum >= 60) {
        func_0209e234(ptr, sum / 60);
        sum = sum % 60;
    }
    *ptr = (unsigned char) sum;
}
