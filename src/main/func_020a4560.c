/* func_020a4560 @ 0x020a4560, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020682e0(int);
extern int func_02068320(int);
extern int func_020b5e10(void);
extern void func_020b6434(int, int, int, int);
extern void func_020a4e94(int, int);

void func_020a4560(int arg)
{
    int *p;
    p = (int *) func_020682e0(0);
    if (p[1] != 0) {
        return;
    }
    func_02068320((int) p);
    func_020b6434(func_020b5e10(), 0x2f, 3, 2);
    func_020a4e94(arg, 0);
}
