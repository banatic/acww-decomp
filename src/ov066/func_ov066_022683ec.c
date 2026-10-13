/* func_ov066_022683ec @ 0x022683ec, 0x24 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

unsigned int func_ov066_022683ec(const unsigned char *p)
{
    return ((unsigned int) p[0] << 24) | ((unsigned int) p[1] << 16) | ((unsigned int) p[2] << 8) | p[3];
}
