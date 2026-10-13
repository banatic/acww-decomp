/* func_ov126_022a0110 @ 0x022a0110, 0xc bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int RtcSendPxiCommand(int cmd);

int func_ov126_022a0110(void)
{
    return RtcSendPxiCommand(0x34);
}
