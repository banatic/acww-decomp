/* func_ov094_022999cc @ 0x022999cc, 0xc bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int RtcSendPxiCommand(int cmd);

int func_ov094_022999cc(void)
{
    return RtcSendPxiCommand(0xc);
}
