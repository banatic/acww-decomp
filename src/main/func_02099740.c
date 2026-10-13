/* func_02099740 @ 0x02099740, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02098ff8(int r0, int r1);
extern void func_02098fd0(int r0, int r1);

void func_02099740(int r0, int r1)
{
    if (r1 != 0) {
        func_02098ff8(r0, 0);
    } else {
        func_02098fd0(r0, 0);
    }
}
