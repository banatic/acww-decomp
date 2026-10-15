/* func_020ea50c @ 0x020ea50c, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ea298(void *region, void *size);
extern int data_021fbe8c;
extern int data_021fbe94;
extern char data_021fbe78;

int func_020ea50c(void *region, void *size)
{
    int res = (int) func_020ea298(region, size);
    if (res) {
        data_021fbe8c = res;
        data_021fbe94 = res;
    }
    data_021fbe78 = 1;
    return res;
}
