/* func_02057a98 @ 0x02057a98, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern __arm void strcpy(void *buf);
extern __arm void NNS_G3dGetResDictIdxByName(void *arg, void *buf);

void func_02057a98(void *arg)
{
    unsigned int buf[4];
    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 0;
    strcpy(buf);
    NNS_G3dGetResDictIdxByName(arg, buf);
}
