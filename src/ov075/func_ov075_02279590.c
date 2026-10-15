/* func_ov075_02279590 @ 0x02279590, 0x4c bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void *arg0);
extern int func_0208602c(void);
extern int func_020860c0(int);
extern int func_02087e38(void *);
extern void func_ov075_022794b8(int, int);

int func_ov075_02279590(int param)
{
    int r4 = param;
    if (func_0202ec58((void *) param) == 0) {
        return 0;
    }
    if (func_02087e38((void *) func_020860c0((int) func_0208602c())) != 0) {
        func_ov075_022794b8(r4, 0);
    } else {
        func_ov075_022794b8(r4, 4);
    }
    *(int *) ((char *) r4 + 0x4e8) |= 2;
    return 1;
}
