/* func_0208ada8 @ 0x0208ada8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a4dc(void *p);
extern void func_0208aeb8(void *p);
extern void func_0208a1f4(void *p);
extern void func_0208af00(void *p);

extern unsigned char data_020e20ac[];

void *func_0208ada8(void *p)
{
    *(void **) p = (void *) data_020e20ac;
    func_0208a4dc(p);
    func_0208aeb8((void *) ((char *) p + 0x90));
    func_0208aeb8((void *) ((char *) p + 0x60));
    func_0208a1f4((void *) ((char *) p + 0x20));
    func_0208a1f4((void *) ((char *) p + 0x0c));
    func_0208af00(p);
    return p;
}
