/* func_02009ea4 @ 0x02009ea4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(char *ptr);
extern int func_02057cf4(void);
extern int func_02009e50(char *p, int a, int b);

void func_02009ea4(char *p)
{
    int result;
    result = func_02056f94(p + 0x2d0);
    if (result != 0 && func_02057cf4() == 5) {
        func_02009e50(p, 6, -1);
    }
}
