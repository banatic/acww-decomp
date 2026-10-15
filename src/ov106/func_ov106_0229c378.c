/* func_ov106_0229c378 @ 0x0229c378, 0x28 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int);
extern void *func_ov002_0220a720(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov106_0229c378(void *param)
{
    void *r4 = param;
    RtcSendPxiCommand(0x27);
    func_ov002_0220a720((char *) r4 + 0x3fb4, 9);
    func_ov002_02208098((void *) (r4), 0x23);
}
