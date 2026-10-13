/* func_02031ca8 @ 0x02031ca8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcb2c(int a, int b, int c);
extern void (*data_020c906c[4])(int);

void func_02031ca8(int a, int b, int c)
{
    data_020c906c[c & 3](func_01ffcb2c(a, b, c));
}
