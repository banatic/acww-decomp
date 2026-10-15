/* func_020afd9c @ 0x020afd9c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203d7b0(int, void *);
extern int func_0203d79c(int, void *);
extern void *func_020644cc(int);
extern void *func_02077f14(void *, const void *);
extern char data_020e41c4[];

void func_020afd9c(void *arg0, void *arg1)
{
    func_0203d7b0(0, arg0);
    func_0203d79c(1, arg1);
    func_02077f14(func_020644cc(2), data_020e41c4);
}
