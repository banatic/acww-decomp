/* func_0208a738 @ 0x0208a738, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a1f0(void *p, const void *q);
extern void func_0208a1ec(void *p, int q);
extern void func_0208a1e8(void *p, int q);
extern const char data_020d71a4[];
extern const char data_020d71ac[];

void func_0208a738(void *p)
{
    func_0208a1f0((char *) p + 0xc, data_020d71a4);
    func_0208a1ec((char *) p + 0xc, 1);
    func_0208a1e8((char *) p + 0xc, 0);
    func_0208a1f0((char *) p + 0x20, data_020d71ac);
    func_0208a1ec((char *) p + 0x20, 1);
    func_0208a1e8((char *) p + 0x20, 0);
}
