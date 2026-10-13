/* func_02070490 @ 0x02070490, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int RtcSendPxiCommand(int cmd);
extern int func_0208b500(void);
extern int func_0208d0bc(int a, int b, int c);
extern int data_020df6a8[];

int func_02070490(int param)
{
    if (param == 0) {
        RtcSendPxiCommand(0x67);
    } else {
        RtcSendPxiCommand(0x66);
    }
    return func_0208d0bc(func_0208b500(), data_020df6a8[param], 0);
}
