/* func_ov144_0229a5bc @ 0x0229a5bc, 0x36 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov144_02299670(void *p, int n);
extern void func_ov144_02299bfc(void *p, int n);
extern void func_ov002_02208098(void *p, int n);
extern void func_ov002_02208090(void *p, int n);
extern void RtcSendPxiCommand(int cmd);

void func_ov144_0229a5bc(void *param0)
{
    func_ov144_02299670(param0, 0x20);
    func_ov144_02299bfc(param0, 8);
    ((unsigned char *) param0)[0xC0] = 5;
    func_ov002_02208098(param0, 0xB);
    func_ov002_02208090(param0, 2);
    RtcSendPxiCommand(0x57);
}
