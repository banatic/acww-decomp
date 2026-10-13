/* func_ov129_0229da60 @ 0x0229da60, 0x1e bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov129_0229d2d0(void *);
extern void func_ov002_022080a0(void *);

int func_ov129_0229da60(void *arg0)
{
    void *r4 = arg0;
    func_ov129_0229d2d0(r4);
    ((unsigned char *) r4)[0x8c] = 0;
    func_ov002_022080a0(r4);
    return 1;
}
