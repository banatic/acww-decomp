/* func_ov114_0229d564 @ 0x0229d564, 0x54 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern int func_02088d34(const void *ptr, int a, int b, int c, int d);
extern int func_ov114_0229cf18(int);
extern int func_ov114_0229cee0(int);
extern char data_ov114_0229dac8;
extern char data_ov114_0229dad0;

int func_ov114_0229d564(int p0, int p1, int p2)
{
    int a = p1 - 0x80;
    int b = p2 - 0x60;
    if (func_02088d34(&data_ov114_0229dac8, a, b, 2, 2)) {
        return func_ov114_0229cf18(p0);
    }
    if (func_02088d34(&data_ov114_0229dad0, a, b, 2, 2)) {
        return func_ov114_0229cee0(p0);
    }
    return 0;
}
