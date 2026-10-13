/* func_ov123_02299ce0 @ 0x02299ce0, 0x20 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a0ec(void *p);

void func_ov123_02299ce0(void *self)
{
    void *p;
    void *q;
    void *(*fn)(void *);

    p = (char *) self + 0x1cc;
    func_ov002_0220a0ec(p);
    q = (char *) self + 0x1cc;
    fn = *(void *(**) (void *) )(*(char **) q + 0xc);
    fn(q);
}
