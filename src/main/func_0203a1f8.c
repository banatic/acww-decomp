/* func_0203a1f8 @ 0x0203a1f8, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020da658;
extern void func_020399c8(void *);
extern void func_0203990c(void *);
extern void func_0203a330(void *);
extern void *func_0203a3ec(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);

void *func_0203a1f8(void *p)
{
    *(void **) p = (void *) &data_020da658;
    func_020399c8(p);
    func_0203990c(p);
    func_0203a330((char *) p + 0x88);
    func_0203a3ec((char *) p + 0x54);
    func_0208a1f4((char *) p + 0x30);
    func_0208a1f4((char *) p + 0x1c);
    func_0208af00(p);
    return p;
}
