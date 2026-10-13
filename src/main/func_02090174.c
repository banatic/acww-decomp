/* func_02090174 @ 0x02090174, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuFill8(void *a, int b, int c);
extern void func_02066650(void *a);
extern void func_020b1a24(void *a);

void func_02090174(char *arg)
{
    MI_CpuFill8(arg, 0, 0x950);
    func_02066650(arg);
    func_020b1a24(arg + 0x100);
}
