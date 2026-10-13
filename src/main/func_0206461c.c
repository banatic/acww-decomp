/* func_0206461c @ 0x0206461c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_020e92e8(void *arg);
extern char data_021cb5a0;

void func_0206461c(unsigned char *arg0)
{
    arg0[1] = (unsigned char) ((func_020e92e8(&data_021cb5a0) >> 31) + 1);
}
