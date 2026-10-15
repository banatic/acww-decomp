/* func_ov104_0229cbe8 @ 0x0229cbe8, 0x24 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_0208f0c4(void *ptr, int value);
extern void RtcSendPxiCommand(int cmd);

void func_ov104_0229cbe8(void *param)
{
    func_ov002_02208098((void *) (param), 0x1a);
    func_0208f0c4((char *) param + 0x2d3c, 2);
    RtcSendPxiCommand(0x29);
}
