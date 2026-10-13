/* func_0202d794 @ 0x0202d794, 0x72 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_02098f48(int a, int b);
extern int func_02098e8c(int a, int i);
extern int func_0204bcdc(unsigned short *p);
extern int func_0204bc64(unsigned short *p);

int func_0202d794(int a, unsigned short *ptr)
{
    unsigned short *p;
    int i;
    int flag1 = 0;
    int flag2 = 0;

    p = func_02098f48(a, 0);
    for (i = 0; i < 15; p++, i++) {
        if (func_02098e8c(a, i) == 2) {
            int result;
            if (func_0204bcdc(p)) {
                int t = func_0204bc64(p);
                result = (t == func_0204bc64(ptr)) ? 1 : flag1;
            } else {
                result = (*p == *ptr) ? 1 : flag2;
            }
            if (result) {
                return i;
            }
        }
    }
    return -1;
}
