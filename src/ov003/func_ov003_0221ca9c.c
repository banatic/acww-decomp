/* func_ov003_0221ca9c @ 0x0221ca9c, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e9948(void *, int);
extern void *memset(int, int, int);
extern void *data_021c9b1c;

int func_ov003_0221ca9c(int a)
{
    int res;

    res = func_020e9948(data_021c9b1c, a);
    memset(res, 0, a);
    return res;
}
