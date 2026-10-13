/* func_02090ebc @ 0x02090ebc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204cab4(void);
extern short data_020e26bc[];

int func_02090ebc(void)
{
    return data_020e26bc[func_0204cab4()];
}
