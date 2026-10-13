/* func_0208a41c @ 0x0208a41c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e2058[];
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);

void *func_0208a41c(void *param)
{
    *(void **) param = (void *) data_020e2058;
    func_0208a1f4((char *) param + 0x20);
    func_0208a1f4((char *) param + 0xc);
    func_0208af00(param);
    return param;
}
