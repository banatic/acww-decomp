/* func_020ab670 @ 0x020ab670, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ab5e4(void *param1);

void func_020ab670(void *param1, int param2, int param3)
{
    func_020ab5e4(param1);
    *(int *) ((char *) param1 + 0x2d0) = param2;
    *(int *) ((char *) param1 + 0x2d4) = param3;
}
