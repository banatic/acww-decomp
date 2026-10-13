/* func_0200fb58 @ 0x0200fb58, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02011490(void *dst, const void *src);

void func_0200fb58(void *a, void *b, void *c)
{
    void *p;
    void *q;

    p = (char *) a + 0x5c;
    func_02011490(p, b);
    q = (char *) p + 8;
    func_02011490(q, c);
}
