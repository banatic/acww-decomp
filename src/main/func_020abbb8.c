/* func_020abbb8 @ 0x020abbb8, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020abc6c(int, int, int);

void func_020abbb8(int p0)
{
    *(int *) ((char *) (p0) + (316)) = 2;
    func_020abc6c(p0, 2, 316);
}
