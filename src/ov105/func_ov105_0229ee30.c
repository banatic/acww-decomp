/* func_ov105_0229ee30 @ 0x0229ee30, 0x28 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229c490(void *p);
extern void func_ov002_02208090(void *p, int n);
extern void func_ov105_0229edec(void *p);

void func_ov105_0229ee30(void *p)
{
    func_ov105_0229c490(p);
    func_ov002_02208090(p, 12);
    ((unsigned char *) p)[0x2c1] = 4;
    func_ov105_0229edec(p);
}
