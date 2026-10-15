/* func_ov105_0229db34 @ 0x0229db34, 0x3c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229d03c(void *);
extern void func_ov105_0229d230(void *);
extern void func_ov105_0229d3b4(void *, unsigned char);
extern void func_ov002_02207fc0(void *);
extern unsigned char *func_ov002_02208098(void *, unsigned char value);

void func_ov105_0229db34(void *p)
{
    unsigned char *base = (unsigned char *) p;
    base[0x2b6] = 0x40;
    func_ov105_0229d03c(p);
    func_ov002_02207fc0(p);
    func_ov105_0229d230(p);
    func_ov002_02208098(p, 7);
    func_ov105_0229d3b4(p, base[0x2ba]);
}
