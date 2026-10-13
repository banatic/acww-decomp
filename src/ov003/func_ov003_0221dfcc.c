/* func_ov003_0221dfcc @ 0x0221dfcc, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056ffc(void *);

void func_ov003_0221dfcc(void *self)
{
    void *p;
    unsigned int *dst;
    unsigned int val;

    p = (char *) self + 0x2b8;
    func_02056ffc(p);
    val = *(unsigned int *) ((char *) self + 0x2c0);
    dst = *(unsigned int **) ((char *) self + 0x2d0);
    *dst = val;
}
