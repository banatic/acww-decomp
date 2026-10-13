/* func_ov112_0229f404 @ 0x0229f404, 0x58 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O1,s
 */

extern void func_ov112_0229fe50(void *self, int param);
extern void func_ov095_02299aec(void *p);
extern int func_ov095_02299b7c(void *p);
extern int func_ov095_02299b38(void *p);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov002_0220a374(void *p, int a);
extern void func_ov112_0229f250(void *self);

void func_ov112_0229f404(void *self)
{
    int a;

    func_ov112_0229fe50(self, 0x800);
    func_ov095_02299aec((char *) self + 0x384);
    a = func_ov095_02299b7c((char *) self + 0x384);
    func_ov002_0220a0b4((char *) self + 0x4448, a, func_ov095_02299b38((char *) self + 0x384));
    func_ov002_0220a374((char *) self + 0x4448, 1);
    func_ov112_0229f250(self);
}
