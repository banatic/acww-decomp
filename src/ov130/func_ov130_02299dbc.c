/* func_ov130_02299dbc @ 0x02299dbc, 0xc bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern int RtcSendPxiCommand(int cmd);

int func_ov130_02299dbc(void)
{
    return RtcSendPxiCommand(0x2a);
}
