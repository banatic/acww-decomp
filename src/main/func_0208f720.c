/* func_0208f720 @ 0x0208f720, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a1f0(void *a, void *b);
extern void func_0208a1ec(void *a, int b);
extern void *func_0208a144(void *a);
extern unsigned char data_020d71f4;

void func_0208f720(void *s)
{
    func_0208a1f0((char *) s + 0xc, &data_020d71f4);
    func_0208a1ec((char *) s + 0xc, 1);
    func_0208a144((char *) s + 0xc);
}
