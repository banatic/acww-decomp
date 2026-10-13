/* func_020beb20 @ 0x020beb20, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020be9f8(void);
extern void func_ov003_022197c4(int, int);

void func_020beb20(int *param)
{
    int local;
    *param = 7;
    local = 1;
    func_ov003_022197c4(local, param[1]);
    func_020be9f8();
}
