/* func_ov004_0223b314 @ 0x0223b314, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov004_022595c0;
extern int func_ov004_0223a7cc(void *p);

int func_ov004_0223b314(void)
{
    void *p = data_ov004_022595c0;
    if (p != 0) {
        return func_ov004_0223a7cc((char *) p + 0x64);
    }
    return 0;
}
