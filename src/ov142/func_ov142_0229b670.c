/* func_ov142_0229b670 @ 0x0229b670, 0x28 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern void func_ov142_02299830(int a, int b);
extern void func_ov142_02299908(int a, int b);
extern void func_ov002_02208098(int a, int b);

void func_ov142_0229b670(int p)
{
    unsigned char f = data_021fbdd8;
    if (f) {
        func_ov142_02299830(p, f);
        return;
    }
    func_ov142_02299908(p, f);
    func_ov002_02208098(p, 0);
}
