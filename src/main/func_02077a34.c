/* func_02077a34 @ 0x02077a34, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02077a34(unsigned char *a, unsigned char *b, unsigned char *c)
{
    if (c) {
        *c = ((unsigned int) *a >> 6) & 3;
    }
    *b = *a & 0x3f;
}
