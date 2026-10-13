/* func_ov115_0229ddd0 @ 0x0229ddd0, 0x28 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a164(void *p);
extern void func_ov002_02208098(void *p, int val);

void func_ov115_0229ddd0(unsigned char *p)
{
    func_ov002_0220a164(p + 0x94);
    p[0x142c] = p[0x8d];
    func_ov002_02208098(p, 5);
}
