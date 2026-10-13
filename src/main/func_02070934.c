/* func_02070934 @ 0x02070934, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b4a20(int a, char *b, char *c);

void func_02070934(int a, char *b, char c)
{
    char temp;
    temp = c;
    func_020b4a20(a, &temp, b);
}
