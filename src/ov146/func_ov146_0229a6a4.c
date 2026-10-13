/* func_ov146_0229a6a4 @ 0x0229a6a4, 0x36 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fc4c(int);
extern void func_ov002_02208090(void *, int);
extern void func_ov002_02208098(void *, int);
extern void RtcSendPxiCommand(int);

void func_ov146_0229a6a4(void *r0)
{
    func_0206fc4c(0);
    ((unsigned char *) r0)[0xb1] = 0xa;
    ((unsigned char *) r0)[0xba] = 5;
    func_ov002_02208090(r0, 2);
    func_ov002_02208098(r0, 9);
    RtcSendPxiCommand(0x28);
}
