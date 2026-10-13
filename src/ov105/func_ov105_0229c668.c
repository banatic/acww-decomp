/* func_ov105_0229c668 @ 0x0229c668, 0x2c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int cmd);
extern void func_ov002_0220a720(void *ptr, int val);
extern void func_ov002_02208098(void *ptr, int val);

void func_ov105_0229c668(void *param)
{
    void *r4 = param;
    RtcSendPxiCommand(0x29);
    func_ov002_0220a720((char *) r4 + 0x5fb8, 9);
    func_ov002_02208098(r4, 0x1b);
    *((unsigned char *) ((char *) r4 + 0x8c)) = 0xe;
}
