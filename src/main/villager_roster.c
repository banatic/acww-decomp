/* villager_roster: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0207c754 @ 0x0207c754, 0x18 bytes, Thumb
 * func_0207c72c @ 0x0207c72c, 0x28 bytes, Thumb
 */

extern void func_02079cc4(char *a, char *b, int c);
extern int func_0207cf14(void *, void *);
extern int func_0207a1c0(int a, int b);

void func_0207c754(char *p, int n)
{
    func_02079cc4(p + 0x3f7c, p, n);
}

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
