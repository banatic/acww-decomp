/* func_0204ed58 @ 0x0204ed58, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02030e4c(int);
extern int func_02031a08(int, int);

int func_0204ed58(int a1, int a2, int a3)
{
    int v1;
    int v2;
    int v3;

    v1 = func_02030e4c(*(int *) (a1 + 0x1c));
    v2 = func_02031a08(a2, a3);
    v3 = func_02030e4c(0);
    return v2;
}
