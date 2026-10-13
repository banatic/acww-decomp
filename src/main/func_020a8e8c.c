/* func_020a8e8c @ 0x020a8e8c, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020512d4(char *p, int arg);
extern void func_0205156c(char *p, int arg);

void func_020a8e8c(char *p, int arg)
{
    int state = *(int *) (p + 0x7c);

    if (state == 1) {
        func_020512d4(p, arg);
    } else if (state == 2) {
        func_0205156c(p, arg);
    }
}
