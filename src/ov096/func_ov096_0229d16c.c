/* func_ov096_0229d16c @ 0x0229d16c, 0x34 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int);
extern void func_ov002_022096d8(void *, int);
extern void func_ov002_02208098(void *, int);
extern void func_ov096_0229ddd8(void *);

void func_ov096_0229d16c(void *r0)
{
    void *r4 = r0;
    RtcSendPxiCommand(0x28);
    *(unsigned char *) ((char *) r4 + 0xbe) = 0xf;
    func_ov002_022096d8((char *) r4 + 0x2564, 1);
    func_ov002_02208098(r4, 0x24);
    func_ov096_0229ddd8(r4);
}
