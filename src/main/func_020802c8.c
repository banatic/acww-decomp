/* func_020802c8 @ 0x020802c8, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020807a8(int a1, int a2);
extern int func_02081c40(int a1, int a2);

int func_020802c8(int a1, int a2, int a3)
{
    int v1;
    int v2;

    v2 = func_020807a8(a1, a3);
    v1 = v2;
    if (v2 != 0) {
        func_02081c40(v2, a2);
    }
    return v1;
}
