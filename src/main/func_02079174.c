/* func_02079174 @ 0x02079174, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_02079350(void);

void func_02079174(unsigned char arg0)
{
    unsigned char *ptr;
    unsigned int offset;

    ptr = (unsigned char *) func_02079350();
    offset = 0x164;
    ptr[offset] = arg0;
}
