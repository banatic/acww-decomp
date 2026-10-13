/* func_02097d50 @ 0x02097d50, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02097d48(void *dest, int value);

void func_02097d50(unsigned char *dest, const unsigned int *src)
{
    dest[2] = (unsigned char) src[0];
    dest[1] = (unsigned char) src[1];
    dest[0] = (unsigned char) src[2];
    func_02097d48(dest, 0x80);
}
