/* func_ov003_02215cbc @ 0x02215cbc, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(int, int b, int c, unsigned short d);
extern void func_0205eae0(int, int, int, int);

void func_ov003_02215cbc(int r0, void *message, int previous)
{
    int r4 = r0;
    func_020109a0(r4, 0x53, 3, 0);
    func_0205eae0(r4 + 0x5a0, 0x16, 3, 0);
}
