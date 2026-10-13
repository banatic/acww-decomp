/* func_0203c558 @ 0x0203c558, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0203c558(unsigned int *arg0);

unsigned int func_0203c558(unsigned int *arg0)
{
    unsigned int *ptr;
    unsigned int value;
    unsigned int result;

    ptr = (unsigned int *) ((unsigned int) arg0 + 0xa0);
    value = *ptr;
    result = value + 0xf0a;
    return result;
}
