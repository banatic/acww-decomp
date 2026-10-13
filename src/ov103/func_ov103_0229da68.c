/* func_ov103_0229da68 @ 0x0229da68, 0x3c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207f04(int, int, int, int, int);
extern void func_ov002_02207e80(int, int, int, int);
extern void func_ov002_02208090(int, int);

void func_ov103_0229da68(int r0)
{
    int sp[2];
    sp[0] = 0x30;
    func_ov002_02207f04(r0, 3, 0, 0, sp[0]);
    func_ov002_02207e80(r0, 3, 0, 0);
    func_ov002_02207e80(r0, 4, 0, 0);
    func_ov002_02208090(r0, 8);
}
