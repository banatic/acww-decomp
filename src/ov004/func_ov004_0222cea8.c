/* func_ov004_0222cea8 @ 0x0222cea8, 0x70 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand();
extern void func_02055060();
extern int func_02055e00();
extern void func_02056440();
extern int func_ov004_0222c3b4();
extern int func_ov004_0222c3c4();

int func_ov004_0222cea8(char *self)
{
    // DECLS
    int v3;
    // ENDDECLS
    func_02055060(self + 0xec, func_ov004_0222c3c4(self + 0x1a4, 0x3), 0x1, 0x1000, 0x0, 0x0);
    v3 = func_02055e00(self + 0xec);
    func_02056440(self + 0x290, v3, func_ov004_0222c3b4(self + 0x1a4, 0x3), 0x1, 0x1000, 0x0);
    RtcSendPxiCommand(0x4ec);
    return 0x1;
}
