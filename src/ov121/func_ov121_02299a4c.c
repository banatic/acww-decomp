/* func_ov121_02299a4c @ 0x02299a4c, 0xe bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

void func_ov121_02299a4c(unsigned short *param0, unsigned short param1)
{
    unsigned short *ptr = (unsigned short *) ((char *) param0 + 0xa2);
    *ptr = (unsigned short) (*ptr | param1);
}
