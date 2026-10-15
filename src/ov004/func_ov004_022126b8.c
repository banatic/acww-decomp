/* func_ov004_022126b8 @ 0x022126b8, 0x1c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223d03c(void);
extern short func_ov004_0223d2ac(int v);
int func_ov004_022126b8(char *self)
{
    *(short *) (self + 0x844) = func_ov004_0223d2ac(func_ov004_0223d03c());
    return 1;
}
