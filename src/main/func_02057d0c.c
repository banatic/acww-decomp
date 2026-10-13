/* func_02057d0c @ 0x02057d0c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021c9350;
extern int func_020598dc(void *, int, int);

int func_02057d0c(int a, int b)
{
    int result = 0;
    if (data_021c9350 != 0) {
        result = func_020598dc(data_021c9350, a, b);
    }
    return result;
}
