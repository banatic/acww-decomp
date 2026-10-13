/* func_ov096_0229c514 @ 0x0229c514, 0x24 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208098(void *self, int cmd);
extern void func_0208f0c4(void *ptr, int val);
extern void RtcSendPxiCommand(int cmd);

void func_ov096_0229c514(void *self)
{
    func_ov002_02208098(self, 0x21);
    func_0208f0c4((char *) self + 0x2d9c, 2);
    RtcSendPxiCommand(0x29);
}
