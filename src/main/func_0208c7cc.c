/* func_0208c7cc @ 0x0208c7cc, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *);
extern __arm void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_0208a1f4(void *);
extern void func_0208c668(void *);
extern void func_0208af00(void *);
extern int data_020e2250;

void *func_0208c7cc(void *p)
{
    *(void **) p = &data_020e2250;
    func_0208c668(p);
    __cxa_vec_cleanup((void *) ((char *) p + 12), 9, 20, (void (*)(void *)) func_0208a1f4);
    func_0208af00(p);
    func_020edb3c(p);
    return p;
}
