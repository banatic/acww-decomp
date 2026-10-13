/* func_ov002_02208014 @ 0x02208014, 0x40 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fe90(int arg);
extern void RtcSendPxiCommand(int cmd);

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;

int func_ov002_02208014(void)
{
    int cond = (data_021fbdd8 != 0) && (data_021fbddc != 0);
    if (cond) {
        func_0206fe90(cond);
        RtcSendPxiCommand(0x866);
        return 1;
    }
    return 0;
}
