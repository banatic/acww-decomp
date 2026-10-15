/* func_02083514 @ 0x02083514, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205d8e8(int);
extern void func_02083cb4(void);

int func_02083514(int x)
{
    func_0205d8e8(x + 1);
    asm { add r0, x, #0 }
    func_02083cb4();
    return x;
}
