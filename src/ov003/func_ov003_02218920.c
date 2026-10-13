/* func_ov003_02218920 @ 0x02218920, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02218bc8(void *);
extern void func_0200f434(void *, int *);
extern void func_02010d64(void *);
extern void func_02010ca4(void *);
extern void func_ov003_02218960(void *);

void func_ov003_02218920(void *p)
{
    int local[4];
    int *base;
    func_ov003_02218bc8(p);
    base = (int *) ((char *) p + 0x7d4);
    local[0] = base[0];
    local[1] = base[1];
    local[2] = base[2];
    func_0200f434(p, local);
    func_02010d64(p);
    func_02010ca4(p);
    func_ov003_02218960(p);
}
