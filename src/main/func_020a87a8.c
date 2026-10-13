/* func_020a87a8 @ 0x020a87a8, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a9ae0(unsigned short *p);

int func_020a87a8(unsigned char *data, int offset)
{
    unsigned char *p = data + offset;
    unsigned short value = p[0] | (p[1] << 8);
    return func_020a9ae0(&value);
}
