/* func_0204eda8 @ 0x0204eda8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02030e4c(int);
extern int func_02031acc(int, int);

int func_0204eda8(int a1, int a2, int a3)
{
    int v1;
    int v2;
    int v3;

    v1 = func_02030e4c(*(int *) (a1 + 0x1c));
    v2 = func_02031acc(a2, a3);
    v3 = func_02030e4c(0);
    return v2;
}
