/* func_0205de94 @ 0x0205de94, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205de10(int);
extern int func_0205ddc0(int, int);
extern int func_0205e0b8(int);
extern int func_0205e0b0(int);
extern int func_02064af4(int, int, int);

int func_0205de94(int a0, int a1)
{
    int v1, v2, v3, v4;
    v1 = func_0205de10(a0);
    v2 = func_0205ddc0(a0, a1);
    if (a1 >= 0x4B) {
        return v2;
    }
    v3 = func_0205e0b8(a1);
    v4 = func_0205e0b0(v3);
    return func_02064af4(v3, v1, v4);
}
