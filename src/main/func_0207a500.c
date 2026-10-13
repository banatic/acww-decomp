/* func_0207a500 @ 0x0207a500, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0207a500(unsigned short *param)
{
    unsigned short *ptr;
    unsigned short val;

    ptr = (unsigned short *) ((unsigned int) param + 0x4078);
    val = *ptr;
    val &= ~2;
    *ptr = val;
    val = *ptr;
    val &= ~0x1c;
    *ptr = val;
}
