/* func_02076ef8 @ 0x02076ef8, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ad7e4(void);

int func_02076ef8(int a, int b, int c, int d)
{
    asm { add r0, d, #0 }
    return func_020ad7e4();
}
