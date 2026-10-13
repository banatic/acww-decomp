/* func_02031d28 @ 0x02031d28, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcb2c(int a, int b, int c);
extern int (*data_020c905c[])(int);

int func_02031d28(int a, int b, int c)
{
    int val = func_01ffcb2c(a, b, c);
    return data_020c905c[c & 3](val);
}
