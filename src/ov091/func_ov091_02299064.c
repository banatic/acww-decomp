/* func_ov091_02299064 @ 0x02299064, 0x4c bytes, Thumb, module ov091
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206e2ec(void *p0, int p1);
extern int func_ov002_0220b53c(void *p0, int p1);
extern int func_ov002_0220b5ec(void *p0, int p1);
extern int func_ov002_0220b59c(void *p0, int p1);
extern void func_ov002_0220a0b4(void *p0, int p1, int p2);

void func_ov091_02299064(void *self)
{
    int r4;
    int r2;
    void *p;

    func_0206e2ec((char *) self + 0x94, 0);
    func_ov002_0220b53c((char *) self + 0x3bc, 0x65);
    r4 = func_ov002_0220b5ec((char *) self + 0x3bc, 1);
    r2 = func_ov002_0220b59c((char *) self + 0x3bc, 1);
    p = (char *) self + 0x434;
    func_ov002_0220a0b4(p, r4, r2);
}
