/* func_ov141_0229ae60 @ 0x0229ae60, 0x1e bytes, Thumb, module ov141
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov141_0229a9b0(void *);
extern unsigned char *func_ov002_022080a0(void *, unsigned char);

int func_ov141_0229ae60(void *p)
{
    func_ov141_0229a9b0(p);
    ((unsigned char *) p)[0x8c] = 0;
    func_ov002_022080a0(p, 0);
    return 1;
}
