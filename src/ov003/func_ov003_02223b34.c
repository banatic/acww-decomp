/* func_ov003_02223b34 @ 0x02223b34, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *dest, int flag, int size, void (*func)(void));
extern void func_ov003_02223b18(void);

void *func_ov003_02223b34(void *p)
{
    func_02138c48((char *) p + 0x18a4, 4, 0x14c, func_ov003_02223b18);
    func_02138c48((char *) p + 0x14c0, 3, 0x14c, func_ov003_02223b18);
    func_02138c48((char *) p + 0x0f90, 4, 0x14c, func_ov003_02223b18);
    func_02138c48(p, 0xc, 0x14c, func_ov003_02223b18);
    return p;
}
