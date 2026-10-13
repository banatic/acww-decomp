/* func_02077978 @ 0x02077978, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020779d8(const unsigned char *src, int arg, unsigned char *dst);
void func_02077978(const unsigned char *p, unsigned int *out, int arg)
{
    unsigned char tmp;
    func_020779d8(p + 2, arg, &tmp);
    *out = (p[1] & 0xFF) | (((tmp << 16) & 0x000F0000) | ((p[0] << 8) & 0x0000FF00));
}
