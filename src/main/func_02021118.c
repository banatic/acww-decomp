/* func_02021118 @ 0x02021118, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202bd7c(void *param0, int param1, int param2);
extern void func_0202bd40(void *param0, int param1, int param2);

int func_02021118(void *param0)
{
    func_0202bd7c(param0, 4, 3);
    func_0202bd40(param0, 5, *(int *) (*(int *) ((char *) param0 + 0x100) + 0x830));
    return func_0202bd7c(param0, 6, 4);
}
