/* func_ov094_022999c0 @ 0x022999c0, 0xc bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int RtcSendPxiCommand(int command);

int func_ov094_022999c0(void)
{
    return RtcSendPxiCommand(0xd);
}
