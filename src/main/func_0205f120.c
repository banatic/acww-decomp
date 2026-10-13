/* func_0205f120 @ 0x0205f120, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0205f120(unsigned char *r0, int r1, unsigned char r2)
{
    unsigned char *ptr;
    int offset;

    offset = r1 << 2;
    ptr = r0 + offset;
    *(unsigned int *) (ptr + 0x0b20) = r2;
}
