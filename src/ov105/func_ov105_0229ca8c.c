/* func_ov105_0229ca8c @ 0x0229ca8c, 0x50 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229c330(unsigned char *param1, int param2);
extern void func_ov002_02208d30(unsigned char *param1, int param2);
extern void func_ov002_02208d4c(unsigned char *param1, int param2, int param3);
extern void func_ov105_0229cbe0(unsigned char *param1, int param2);

void func_ov105_0229ca8c(unsigned char *base)
{
    func_ov105_0229c330(base, 0x800);
    func_ov002_02208d30(base + 0x28f0, 4);
    func_ov002_02208d4c(base + 0x28f0, 0x1a, 4);
    func_ov002_02208d4c(base + 0x28f0, 0x15, 2);
    func_ov002_02208d4c(base + 0x28f0, 0x19, 4);
    func_ov105_0229cbe0(base, 0);
}
