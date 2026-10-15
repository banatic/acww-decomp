/* func_ov105_0229c62c @ 0x0229c62c, 0x3c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int);
extern void *func_ov002_0220a720(int, int);
extern void func_ov105_0229c320(int, int);
extern unsigned char *func_ov002_02208098(int, unsigned char value);

void func_ov105_0229c62c(int param)
{
    int local;
    RtcSendPxiCommand(0x27);
    local = param + 0x5fb8;
    func_ov002_0220a720(local, 3);
    *(unsigned char *) (param + 0x8c) = 4;
    func_ov105_0229c320(param, 0x100);
    func_ov002_02208098(param, 0x1b);
}
