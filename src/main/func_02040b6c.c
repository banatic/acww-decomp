/* func_02040b6c @ 0x02040b6c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void);
extern int func_0209ded0(void);
extern void func_0209e140(int, int);
extern void func_0209e29c(int, int);

void func_02040b6c(int a0, int a1)
{
    func_0209e474();
    if (a1 == 1) {
        int s = func_0209ded0() + 1;
        func_0209e140(a0, s);
    } else {
        int s = 7 - func_0209ded0();
        func_0209e29c(a0, s);
    }
}
