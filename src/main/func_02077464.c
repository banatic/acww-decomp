/* func_02077464 @ 0x02077464, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02235c94(void *buffer, int index);

void func_02077464(int p0, int p1)
{
    asm { add r2, p1, #0 }
    func_ov003_02235c94((void *) p0, 25);
}
