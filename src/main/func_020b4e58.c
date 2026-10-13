/* func_020b4e58 @ 0x020b4e58, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050c10(int param);
extern int func_020a9334(int param1, int param2);

int func_020b4e58(int param)
{
    return func_020a9334(param, func_02050c10(param));
}
