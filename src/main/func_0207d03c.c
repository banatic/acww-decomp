/* func_0207d03c @ 0x0207d03c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0209a7e8(void *);
extern void func_0207a334(void *);
extern void func_02079cbc(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void *func_02081710(void *);

void *func_0207d03c(void *p)
{
    func_0209a7e8((char *) p + 0x3f90);
    func_0207a334((char *) p + 0x3f7c);
    func_02079cbc((char *) p + 0x3f60);
    __cxa_vec_cleanup((void *) (p), 8, 0x7ec, (((void (*)(void *)) func_02081710)));
    return p;
}
