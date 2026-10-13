/* func_ov129_0229c758 @ 0x0229c758, 0x44 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov129_0229b7dc(void *, int);
extern void func_ov002_0220a720(void *, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov002_02208098(void *, int);
extern void func_ov129_0229b7cc(void *, int);
extern void RtcSendPxiCommand(int);

void func_ov129_0229c758(void *param)
{
    func_ov129_0229b7dc(param, 4);
    func_ov002_0220a720((char *) param + 0x1d4, 5);
    func_ov002_02208090(param, 4);
    func_ov002_02208098(param, 0xa);
    func_ov129_0229b7cc(param, 0x10);
    RtcSendPxiCommand(0x2a);
    func_ov129_0229b7cc(param, 0x80);
}
