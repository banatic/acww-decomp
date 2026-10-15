/* func_ov002_0220a568 @ 0x0220a568, 0xc bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e95c(void *object, int index);

int func_ov002_0220a568(int a)
{
    register int result;
    func_0208e95c((void *) a, 3);
    asm {
            mov result, r0
    }
    return result;
}
