/* func_020950d4 @ 0x020950d4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern __arm unsigned int func_020644cc(unsigned int);

unsigned short func_020950d4(void)
{
    unsigned short t = (unsigned short) func_020644cc(0x7ffc);
    return (unsigned short) (t | 0x8000);
}
