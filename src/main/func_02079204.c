/* func_02079204 @ 0x02079204, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02079350(void);

void func_02079204(unsigned char arg0)
{
    unsigned char *ptr;
    ptr = (unsigned char *) func_02079350();
    ptr[0x162] = arg0;
}
