/* func_ov003_0221e0d4 @ 0x0221e0d4, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056ffc(void *);

void func_ov003_0221e0d4(void *self)
{
    int *p;
    int *q;
    int v;

    func_02056ffc((char *) self + 0x2b8);
    p = (int *) ((char *) self + 0x2c0);
    q = *(int **) ((char *) self + 0x2d0);
    v = *p;
    *q = v;
}
