/* func_0207e684 @ 0x0207e684, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02099734(int);
extern int func_02098eb8(int);

int func_0207e684(int object)
{
    int r0;
    int r2;
    int r1;

    r0 = func_02099734(object);
    r0 = func_02098eb8(r0);
    r2 = 0;
    r1 = ~r2;
    if (r0 != r1) {
        r2 = 0;
    } else {
        r2 = 1;
    }
    r0 = r2;
    return r0;
}
