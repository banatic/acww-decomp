/* func_020483c4 @ 0x020483c4, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct Global data_021c79c4;
extern int func_020644cc(int);
extern void func_02048cb8(int, int, int, int, int, void (*)(void), int);
extern void func_02048ee4(void);

struct Global {
    char pad_00[0x30];
    int : 5;
    int flag : 1;
    int : 26;
};

void func_020483c4(int p0, int p1, int p2, int p3)
{
    int t1, t2;
    if (data_021c79c4.flag) {
        return;
    }
    t1 = func_020644cc(p2 - 1);
    t2 = func_020644cc(p3 - 1);
    func_02048cb8(p0, p1, t1 + 1, t2 + 1, 0x1566, func_02048ee4, 1);
}
