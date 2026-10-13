/* func_02044a14 @ 0x02044a14, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02044a30(void *a, void *b, int c, int d);

void func_02044a14(unsigned int *p0, unsigned int *p1, int a2, int a3)
{
    unsigned int local[2];
    local[0] = p1[0];
    local[1] = p1[1];
    func_02044a30(p0, local, a2, a3);
}
