/* func_02077a8c @ 0x02077a8c, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073dd4(void *self, int idx);
extern int func_02073918(void *self, int idx);
extern int func_02073d10(void *self, int idx);
extern void *data_020ccf94;

int func_02077a8c(unsigned short flags)
{
    int i = 3;
    void *p = data_020ccf94;

    for (; i >= 0; i--) {
        if (func_02073dd4(p, i) == 0) {
            continue;
        }
        if (func_02073918(p, i) != 0) {
            continue;
        }
        if (((unsigned short) (1 << i) & flags) == 0) {
            continue;
        }
        if (func_02073d10(p, i) != 0) {
            continue;
        }
        return 0;
    }
    return 1;
}
