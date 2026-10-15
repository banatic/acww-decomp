/* func_02083294 @ 0x02083294, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0205ef90(void *arg);
extern void func_02083cb4(void);
void *func_02083294(void *arg)
{
    func_0205ef90((char *) arg + 4);
    asm { add r0, arg, #0 }
    func_02083cb4();
    return arg;
}
