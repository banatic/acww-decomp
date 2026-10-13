/* func_ov004_0223b28c @ 0x0223b28c, 0x20 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov004_022595c0;
extern int func_ov004_0223a790(void *p);

int func_ov004_0223b28c(void)
{
    void *p = data_ov004_022595c0;
    if (p != 0) {
        return func_ov004_0223a790((char *) p + 0x64);
    }
    return 0;
}
