/* func_ov003_02211df8 @ 0x02211df8, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(int);
extern int func_02008258(int, int);
extern void func_0200d4e8(int, int, int, int);

void func_ov003_02211df8(int r0)
{
    int r4;
    int r1;
    int r2;
    int r3;

    r4 = r0;
    if (func_02056f94(r4 + 0x2d0) != 0) {
        r1 = *(int *) (r4 + 0x7f0);
        r0 = func_02008258(r4, r1);
        *(int *) (r4 + 0x7fc) = r0;
        func_0200d4e8(r4, 3, 1, -1);
    }
}
