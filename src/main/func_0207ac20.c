/* func_0207ac20 @ 0x0207ac20, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0207ac40(void *param1, int param2);

void func_0207ac20(void *param1)
{
    int i;
    void *p;

    p = param1;
    i = 0;
    do {
        func_0207ac40(p, i);
        i++;
    } while (i < 8);
}
