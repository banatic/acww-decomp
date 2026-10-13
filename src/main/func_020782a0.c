/* func_020782a0 @ 0x020782a0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051bf8(void *param1, void *param2);

void func_020782a0(void *param1, void *param2)
{
    unsigned char *dst;
    unsigned char *src;
    unsigned char val;

    src = (unsigned char *) param2;
    dst = (unsigned char *) param1;

    val = src[0];
    dst[0xc0] = val;
    val = src[1];
    dst[0xc1] = val;
    val = src[2];
    dst[0xc2] = val;
    dst[0xc3] = 0;

    func_02051bf8(param1, (void *) 0x60);
}
