/* func_02098580 @ 0x02098580, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02099ad0(void);
extern void func_02138c48(int, int, int, void (*)(void));

int func_02098580(int arg)
{
    func_02138c48(arg, 3, 0x249C, func_02099ad0);
    return arg;
}
