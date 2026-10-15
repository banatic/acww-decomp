/* func_0207c72c @ 0x0207c72c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207cf14(void *, void *);
extern int func_0207a1c0(int a, int b);

int func_0207c72c(int r4, void *argument1)
{
    int r0;
    int r1;
    int r2;
    int r3;

    r0 = func_0207cf14((void *) r4, (void *) argument1);
    r1 = r0;
    r0 = func_0207a1c0(r4 + 0x3f7c, r1);
    r2 = 0;
    r1 = ~r2;
    if (r0 == r1) {
        r2 = 0;
    } else {
        r2 = 1;
    }
    r0 = r2;
    return r0;
}
