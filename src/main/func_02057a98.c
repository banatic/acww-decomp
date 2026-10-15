/* func_02057a98 @ 0x02057a98, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern __arm unsigned char *strcpy(void *dst, const char *src);
extern __arm int NNS_G3dGetResDictIdxByName(void *arg, void *buf);

int func_02057a98(void *arg, const char *name)
{
    unsigned int buf[4];
    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 0;
    strcpy(buf, name);
    return NNS_G3dGetResDictIdxByName(arg, buf);
}
