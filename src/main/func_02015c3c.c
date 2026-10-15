/* func_02015c3c @ 0x02015c3c, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02015d44(void);
extern int func_02095794(int);
extern int func_0200322c(int a, void *b);
extern void *func_02096190(int a);
extern int func_02095518(int a, int b, int c);

int func_02015c3c(int a, int b)
{
    int r5 = func_02015d44();
    int cond = func_02095794(r5);
    if (cond != 0) {
        int r4 = func_0200322c(cond, (char *) b + 0x5c);
        int diff = (short) (r4 - *(short *) ((char *) func_02096190(4) + 0x8e));
        return func_02095518(0, diff, r5);
    }
    return cond;
}
