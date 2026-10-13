/* func_02096ebc @ 0x02096ebc, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned char func_02096ebc(int r0)
{
    if (r0 >= 0 && r0 < 0x22) {
        return (unsigned char) r0;
    }
    if (r0 >= 0x22 && r0 < 0x5a) {
        return (unsigned char) (r0 - 0x22);
    }
    return (unsigned char) (r0 - 0x5a);
}
