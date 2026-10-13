/* func_ov103_0229c604 @ 0x0229c604, 0x3c bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *p, int v);
extern void func_ov002_0220a374(void *p, int v);
extern void func_ov002_02208098(void *p, int v);

void func_ov103_0229c604(void *p, unsigned char v)
{
    func_ov002_02207d24((char *) p + 0x218c, 1);
    *((unsigned char *) ((char *) p + 0x2da6)) = v;
    func_ov002_0220a374((char *) p + 0x2274, 5);
    func_ov002_02208098(p, 0x10);
}
