/* func_ov004_0220e640 @ 0x0220e640, 0x32 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200322c();
extern int func_02095794();
extern int func_ov004_0220e73c();
extern void func_ov004_0220fefc();

int func_ov004_0220e640(char *self)
{
    // DECLS
    int v1;
    char frame[0xc];
    // ENDDECLS
    v1 = func_02095794(0x4);
    if (v1 != 0x0) {
        func_ov004_0220fefc(self, frame);
        return func_ov004_0220e73c(frame, func_0200322c(frame, v1));
    }
    return v1;
}
