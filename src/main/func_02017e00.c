/* func_02017e00 @ 0x02017e00, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057bd4(void);
extern void func_02019af0(void *param, int val);

void func_02017e00(void *param, int event)
{
    if (func_02057bd4() == 0) {
        func_02019af0(param, 1);
        *((char *) param + 0x98) = 0x14;
    }
}
