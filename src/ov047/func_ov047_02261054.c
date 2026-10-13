/* func_ov047_02261054 @ 0x02261054, 0x14 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern void func_02014f60(void);

void func_ov047_02261054(void *p)
{
    func_02014f60();
    *(unsigned int *) ((char *) p + 0xd0) = 0x6b;
}
