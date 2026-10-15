/* func_0200322c @ 0x0200322c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern short func_020e8ed8(int, int);

short func_0200322c(int *a, int *b)
{
    int r0, r1;
    int *r3;

    r3 = a;
    r0 = *b - *r3;
    r1 = *(b + 2) - *(r3 + 2);
    return func_020e8ed8(r0, r1);
}
