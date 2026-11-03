/* clock_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209dee8 @ 0x0209dee8, 0xc bytes, Thumb
 * func_0209dedc @ 0x0209dedc, 0xc bytes, Thumb
 */

extern int data_021dc744;

int func_0209dee8(void)
{
    return data_021dc744;
}

int func_0209dedc(void)
{
    return *(int *) ((char *) ((int) &data_021dc744) + (24));
}
