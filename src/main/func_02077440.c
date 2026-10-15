/* func_02077440 @ 0x02077440, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02235c94(void *buffer, int index);
void func_02077440(int a, int b)
{
    asm { add r2, b, #0 }
    func_ov003_02235c94((void *) a, 28);
}
