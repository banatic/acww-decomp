/* func_ov122_0229f0a8 @ 0x0229f0a8, 0x34 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int);
extern void func_ov002_022096d8(void *, int);
extern void func_ov002_02208098(void *, int);
extern void func_ov122_0229f2d0(void *);

void func_ov122_0229f0a8(void *arg0)
{
    RtcSendPxiCommand(0x28);
    ((unsigned char *) arg0)[0xb6] = 0xf;
    func_ov002_022096d8((char *) arg0 + 0x42b0, 1);
    func_ov002_02208098(arg0, 0x18);
    func_ov122_0229f2d0(arg0);
}
