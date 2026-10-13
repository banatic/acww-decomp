/* func_02069270 @ 0x02069270, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8328(char *p, int *a, int *b, int *c);
extern int func_02068114(void);
extern void func_0206bf78(char *p, int b, int a, int flag);
extern void func_0206bf3c(char *p, int c, int d, int flag);
extern void func_020a93e8(char *p, int shifted);

void func_02069270(char *p)
{
    int a, b, c;
    int flag;

    func_020a8328(p + 0x38, &a, &b, &c);
    flag = func_02068114();
    func_0206bf78(p + 0x60, b, a, flag);
    func_0206bf3c(p + 0x9c, c, c + ((b - c) ^ 1), !flag);
    func_020a93e8(p, a << 1);
}
