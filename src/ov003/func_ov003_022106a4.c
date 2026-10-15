/* func_ov003_022106a4 @ 0x022106a4, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022108b0(void *p);
extern void func_ov003_022107ac(void *p);
extern int func_0200f434(void *p, void *q);
extern void func_02010d64(void *p);
extern void func_ov003_022106e4(void *p);

void func_ov003_022106a4(void *p)
{
    int *base;
    int tmp[3];
    int i;

    func_ov003_022108b0(p);
    func_ov003_022107ac(p);

    base = (int *) ((char *) p + 0x7d4);
    tmp[0] = base[1];
    tmp[1] = base[2];
    tmp[2] = base[3];

    func_0200f434(p, tmp);
    func_02010d64(p);
    func_ov003_022106e4(p);
}
