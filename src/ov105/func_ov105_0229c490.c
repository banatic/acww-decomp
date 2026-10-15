/* func_ov105_0229c490 @ 0x0229c490, 0x3c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229cfc0(void *);
extern int func_ov002_02207d24(void *, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov002_02207e90(void *, int);

void func_ov105_0229c490(void *p)
{
    func_ov002_02207d24((char *) p + 0x23bc, 1);
    func_ov105_0229cfc0(p);
    func_ov002_02207f04(p, 2, 0, 2, 0x30);
    func_ov002_02207e90(p, 0xc0);
}
