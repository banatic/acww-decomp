/* func_02056a4c @ 0x02056a4c, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056a64(int a);
extern void func_020ba004(int a);

int func_02056a4c(int arg)
{
    func_02056a64(arg);
    func_020ba004(arg + 4);
    return 1;
}
