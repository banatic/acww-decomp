/* func_0203ab34 @ 0x0203ab34, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int command);

void func_0203ab34(unsigned char *param0, int param1)
{
    if (param0[0x1f7] == 0) {
        RtcSendPxiCommand(param1);
    }
}
