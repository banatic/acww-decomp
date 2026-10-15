/* func_ov004_0220e640 @ 0x0220e640, 0x32 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200322c(int *argument0, int *argument1);
extern int func_02095794(int argument0);
extern int func_ov004_0220e73c(char *arg0, int arg1);
extern void func_ov004_0220fefc(char *argument0, int *argument1);

int func_ov004_0220e640(char *self)
{
    // DECLS
    int v1;
    char frame[0xc];
    // ENDDECLS
    v1 = func_02095794(0x4);
    if (v1 != 0x0) {
        func_ov004_0220fefc((char *) (self), (int *) (frame));
        return func_ov004_0220e73c(frame, func_0200322c((int *) (frame), (int *) (v1)));
    }
    return v1;
}
