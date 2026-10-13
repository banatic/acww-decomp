/* func_0204e3bc @ 0x0204e3bc, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f800(void *a, void *b, int c, int d, int e, int f);
extern void func_0204e3f4(int a, int b, int c, int d);

void func_0204e3bc(int a, int b, int c, int d, int e, int f)
{
    int local1;
    int local2;
    int local3;
    int local4;

    local1 = 0;
    local2 = 0;
    local3 = d;
    local4 = e;
    func_0204f800(&local1, &local2, b, c, local3, local4);
    func_0204e3f4(a, local1, local2, f);
}
