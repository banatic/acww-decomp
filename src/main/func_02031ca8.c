/* func_02031ca8 @ 0x02031ca8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcb2c(int a, int b);
extern int (*data_020c906c[4])(int);

int func_02031ca8(int a, int b, int c)
{
    return data_020c906c[c & 3](func_01ffcb2c(a, b));
}
