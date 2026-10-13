/* func_0204bbd4 @ 0x0204bbd4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0204bbd4(unsigned int a)
{
    unsigned int v;
    if (a < 0x22) {
        v = a + 0x5000;
    } else {
        v = 0x5000;
    }
    return (unsigned short) v;
}
