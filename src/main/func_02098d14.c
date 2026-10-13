/* func_02098d14 @ 0x02098d14, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_02098f48(void *data, int flag);
extern int func_0204c878(unsigned short *p);
extern int func_02098e8c(void *data, int index);

int func_02098d14(void *data, int base)
{
    unsigned short *p;
    int i;
    int r7;
    int result;
    unsigned short local;

    p = func_02098f48(data, 0);
    local = 0x14fd;
    r7 = func_0204c878(&local);
    result = base * r7;
    i = 0;
    for (; i < 15; p++, i++) {
        unsigned short v = *p;
        if (v == 0xfff1) {
            result += r7;
        } else if (v >= 0x1492 && v <= 0x14fd) {
            if (func_02098e8c(data, i) == 0) {
                result += r7 - func_0204c878(p);
            }
        }
    }
    return result;
}
