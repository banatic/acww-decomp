/* func_ov105_0229ed04 @ 0x0229ed04, 0x30 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229c3c8(void);
extern void func_ov002_02207eb4(void *p, int a, int b);
extern void func_ov002_0220a960(void *p, int a);
extern void func_ov002_02208090(void *p, int a);

void func_ov105_0229ed04(void *p)
{
    func_ov105_0229c3c8();
    func_ov002_02207eb4(p, 0, 0);
    func_ov002_0220a960((char *) p + 0x5fb8, 0x22);
    func_ov002_02208090(p, 0x11);
}
