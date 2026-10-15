/* func_02060460 @ 0x02060460, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_0222aae8(unsigned int);
void func_02060460(void *param)
{
    unsigned int val = *(unsigned int *) ((char *) param + 0x2c);
    func_ov003_0222aae8(val);
    *(unsigned int *) ((char *) param + 0x2c) = 0;
}
