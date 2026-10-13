/* func_020731c4 @ 0x020731c4, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073dd4(void *p, int idx);
extern int func_02073918(void *p, int idx);
extern void func_02077b58(int idx);
extern unsigned int func_02073220(void *p, int idx);
extern void func_02077a64(unsigned int v);

int func_020731c4(void)
{
    int idx = 3;
    void *p = data_020ccf94;

    while (idx >= 0) {
        if (func_02073dd4(p, idx) && !func_02073918(p, idx)) {
            unsigned int result;

            func_02077b58(idx);
            result = func_02073220(p, idx);
            func_02077a64(result);
            if (result > 600U) {
                return 1;
            }
        }
        idx--;
    }
    return 0;
}
