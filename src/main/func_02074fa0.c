/* func_02074fa0 @ 0x02074fa0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073dd4(void *p, int i);
extern int func_02073918(void *p, int i);
extern int func_02073d28(void *p, int i);
extern int func_02073c90(void *p, int i);
extern int func_02077b50(int a, int b);

void func_02074fa0(void)
{
    int i = 3;
    void *base = data_020ccf94;
    for (; i >= 0; i--) {
        if (func_02073dd4(base, i) != 0) {
            if (func_02073918(base, i) == 0) {
                func_02077b50(func_02073d28(base, i), func_02073c90(base, i));
            }
        }
    }
}
