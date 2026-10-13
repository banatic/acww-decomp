/* func_0204bbbc @ 0x0204bbbc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_0204bbbc(unsigned int x);

unsigned short func_0204bbbc(unsigned int x)
{
    unsigned int y;
    if (x < 8) {
        y = x + 0x5001;
    } else {
        y = 0x5001;
    }
    return (unsigned short) y;
}
