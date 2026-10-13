/* func_ov004_0223b2ec @ 0x0223b2ec, 0x28 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223a7f0(void *);
extern void *data_ov004_022595c0;

short func_ov004_0223b2ec(void)
{
    if (data_ov004_022595c0 != 0) {
        return (short) func_ov004_0223a7f0((char *) data_ov004_022595c0 + 0x64);
    }
    return -1;
}
