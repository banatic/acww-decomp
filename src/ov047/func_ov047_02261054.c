/* func_ov047_02261054 @ 0x02261054, 0x14 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014f60(int argument0);

void func_ov047_02261054(void *p)
{
    func_02014f60((int) p);
    *(unsigned int *) ((char *) p + 0xd0) = 0x6b;
}
