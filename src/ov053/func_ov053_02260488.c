/* func_ov053_02260488 @ 0x02260488, 0x34 bytes, Thumb, module ov053
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern unsigned short *func_020996e0(int a);
extern unsigned short *func_020996f8(int a);

int func_ov053_02260488(void *receiver)
{
    int a = func_020984e8();
    if (!(*func_020996e0(a) == 0xfff1 && *func_020996f8(a) == 0xfff1)) {
        return 1;
    }
    return 0;
}
