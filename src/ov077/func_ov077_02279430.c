/* func_ov077_02279430 @ 0x02279430, 0x44 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void);
extern void func_0203edf4(int, int);
extern void func_ov077_02279358(int, int);
extern void func_0203edd0(int);
extern void func_0203e310(void);

int func_ov077_02279430(int param)
{
    int result;
    int *ptr;

    if (func_0202ec58() == 0) {
        return 0;
    }
    ptr = (int *) ((char *) param + 0x4e8);
    *ptr |= 2;
    func_0203edf4(param, 0);
    func_ov077_02279358(param, 3);
    func_0203edd0(param);
    func_0203e310();
    return 1;
}
