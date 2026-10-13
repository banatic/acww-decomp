/* func_020bf2a0 @ 0x020bf2a0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bf2b8(int, int, int, int);

void func_020bf2a0(int a0, int a1)
{
    int r3 = a0;
    int r0 = a1;
    int r1 = *(int *) (r3 + 0x34);
    int r2 = *(int *) (r3 + 0x38);
    int r3_2 = *(int *) (r3 + 0x4c);
    func_020bf2b8(r0, r1, r2, r3_2);
}
