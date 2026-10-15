/* func_0208f640 @ 0x0208f640, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8cac(void *p);
extern void func_020a8c1c(void *p);
extern unsigned char data_020e2388;

void *func_0208f640(void *p)
{
    func_020a8cac(p);
    *(void **) p = (void *) &data_020e2388;
    func_020a8c1c(p);
    return p;
}
