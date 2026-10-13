/* func_020abb8c @ 0x020abb8c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void RtcSendPxiCommand(int);
extern void func_020abb78(void *);

void func_020abb8c(void *param)
{
    void *r4;
    r4 = param;
    if (func_0208e484((char *) param + 0x20)) {
        if (((unsigned char *) r4)[0x145]) {
            RtcSendPxiCommand(0x33);
        }
        func_020abb78(r4);
    }
}
