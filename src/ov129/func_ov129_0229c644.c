/* func_ov129_0229c644 @ 0x0229c644, 0x40 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov129_0229b7ec(void *a, int b);
extern void RtcSendPxiCommand(int cmd);
extern void *func_ov002_0220a720(void *a, int b);
extern void func_ov002_02208090(void *a, int b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov129_0229c644(void *p)
{
    if (func_ov129_0229b7ec(p, 4) != 0) {
        RtcSendPxiCommand(0x29);
    } else {
        RtcSendPxiCommand(0x2a);
    }
    func_ov002_0220a720((char *) p + 0x1d4, 4);
    func_ov002_02208090(p, 8);
    func_ov002_02208098((void *) (p), 0xa);
}
