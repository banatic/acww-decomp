/* func_020786d8 @ 0x020786d8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020786d8(unsigned int *a, unsigned char *b, unsigned char *c, const unsigned char *d)
{
    *a = (*d >> 4) & 0xF;
    *b = *d & 0xF;
    *c = d[1];
}
