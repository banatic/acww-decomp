/* func_02017550 @ 0x02017550, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057bf0(int param0);
extern void func_02019af0(void *param0, int param1);

void func_02017550(unsigned char *obj, int event)
{
    if (func_02057bf0(8) == 0) {
        obj[0x98] = 2;
        func_02019af0(obj, 1);
    }
}
