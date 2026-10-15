/* func_020979ac @ 0x020979ac, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02097958(void *);
extern int func_02097900(int param);

int func_020979ac(int param)
{
    int ret1 = func_02097958((void *) param);
    if (ret1 == -2) {
        return 0;
    }
    if (ret1 == -1) {
        int ret2 = func_02097900(param);
        if (ret2 == -2) {
            return 0;
        }
        if (ret2 == -1) {
            return 0;
        }
    }
    return 1;
}
