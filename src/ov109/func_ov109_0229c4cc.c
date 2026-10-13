/* func_ov109_0229c4cc @ 0x0229c4cc, 0x28 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a720(char *, int);
extern void func_ov002_02208098(char *, int);
extern int RtcSendPxiCommand(int);

int func_ov109_0229c4cc(char *s)
{
    func_ov002_0220a720(s + 0x27e8, 9);
    func_ov002_02208098(s, 0xf);
    return RtcSendPxiCommand(0x28);
}
