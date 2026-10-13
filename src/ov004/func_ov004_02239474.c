/* func_ov004_02239474 @ 0x02239474, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e92e8(void *p);
extern int func_ov004_02239460(void *b, void *a);
extern int data_021cb5a0;
short func_ov004_02239474(void *a, void *b)
{
    int s;
    if (func_020e92e8(&data_021cb5a0) > 0) {
        s = 1;
    } else {
        s = -1;
    }
    return (short) (0xb6 * (func_ov004_02239460(b, a) * (signed char) s));
}
