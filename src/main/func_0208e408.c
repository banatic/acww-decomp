/* func_0208e408 @ 0x0208e408, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e2a4(void *);
extern void func_0203a3ec(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);

extern unsigned char data_020e22f8[];

void *func_0208e408(void *s)
{
    *(void **) s = (void *) data_020e22f8;
    func_0208e2a4(s);
    func_0203a3ec((char *) s + 0x38);
    func_0208a1f4((char *) s + 0x14);
    func_0208af00(s);
    return s;
}
