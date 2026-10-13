/* func_020b11a4 @ 0x020b11a4, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b1580(char *arg);
extern int func_020b1078(char *arg);
extern void func_020b11fc(void);
extern int func_ov127_022995a0(char *arg);
extern void func_020b11ec(void);
extern void func_020b14ec(char *arg, int x, int y);

int func_020b11a4(char *arg)
{
    int x;
    int result;
    x = func_020b1580(arg);
    if (x == -1) {
        return 0;
    }
    if (func_020b1078(arg + 0x1e) != 0) {
        return 0;
    }
    func_020b11fc();
    result = func_ov127_022995a0(arg);
    func_020b11ec();
    if (result != 0) {
        func_020b14ec(arg, x, 1);
    }
    return result;
}
