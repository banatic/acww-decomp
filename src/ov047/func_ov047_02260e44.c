/* func_ov047_02260e44 @ 0x02260e44, 0x14 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern void func_02014f60(void);

void func_ov047_02260e44(void *arg)
{
    func_02014f60();
    *(unsigned int *) ((char *) arg + 0xd0) = 0x20;
}
