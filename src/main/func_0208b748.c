/* func_0208b748 @ 0x0208b748, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200452c(void);
extern void func_0200453c(void);
extern void RtcSendPxiCommand(int);

void func_0208b748(unsigned char *param0, unsigned char param1)
{
    unsigned char *r5;
    unsigned char r4;

    r5 = param0;
    r4 = param1;

    if (param0[0x81] != 0) {
        if (r4 == 0) {
            func_0200452c();
            RtcSendPxiCommand(0x2e);
        }
    } else {
        if (r4 != 0) {
            func_0200453c();
        }
    }

    r5[0x81] = r4;
}
