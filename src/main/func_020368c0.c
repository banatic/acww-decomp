/* func_020368c0 @ 0x020368c0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6660(void);
extern int func_020b6640(void);
extern void func_02036e90(void *);
extern void func_02036fd4(void *);
extern void func_0203723c(void *);

void func_020368c0(void *param)
{
    if (func_020b6660() == 0 && func_020b6640() == 0) {
        return;
    }
    func_02036e90((char *) param + 0x24);
    func_02036fd4((char *) param + 0x18);
    func_0203723c((char *) param + 4);
}
