/* func_ov131_0229b04c @ 0x0229b04c, 0x30 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int);
extern void func_0206fc4c(int);
extern void *func_ov002_0220a720(void *, int);
extern void func_ov002_02208090(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov131_0229b04c(void *r0)
{
    RtcSendPxiCommand(0x2a);
    func_0206fc4c(0);
    func_ov002_0220a720((char *) r0 + 0xf8, 7);
    func_ov002_02208090(r0, 2);
    func_ov002_02208098((void *) (r0), 7);
}
