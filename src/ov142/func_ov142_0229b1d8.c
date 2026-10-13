/* func_ov142_0229b1d8 @ 0x0229b1d8, 0x24 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov142_0229b0d4(void *);
extern void func_ov002_02207fc0(void *);
extern void func_ov002_02208098(void *, int);

void func_ov142_0229b1d8(void *p)
{
    ((unsigned char *) p)[0xc0] = 0x18;
    func_ov142_0229b0d4(p);
    func_ov002_02207fc0(p);
    func_ov002_02208098(p, 0xc);
}
