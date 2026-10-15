/* func_02083da4 @ 0x02083da4, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208602c(void);
extern int func_020860c0(int);
extern void func_02087e4c(int, int);
extern int func_02087de8(int);

int func_02083da4(int param0, int param1, int param2)
{
    int res;
    res = func_020860c0((int) func_0208602c());
    func_02087e4c(res, param1);
    *(unsigned short *) (param2 + 2) = (unsigned short) func_02087de8(res);
    return 1;
}
