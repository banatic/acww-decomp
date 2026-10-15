/* func_ov121_0229b340 @ 0x0229b340, 0x3c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov121_02299a4c(int, int);
extern void RtcSendPxiCommand(int command);
extern int func_ov002_02209f9c(int);
extern unsigned char *func_ov002_02208098(int, unsigned char value);

void func_ov121_0229b340(int param)
{
    if (func_ov002_02209f9c(param + 0x3a8) != 0) {
        func_ov002_02208098(param, 10);
        *(unsigned char *) (param + 0xae) = *(unsigned char *) (param + 0xb1);
        func_ov121_02299a4c(param, 4);
        RtcSendPxiCommand(0xd);
    }
}
