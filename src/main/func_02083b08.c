/* func_02083b08 @ 0x02083b08, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e1b54;
extern void func_02083bac(void);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void));
extern void func_02083c78(void *);
extern void func_020edb3c(void *);

void *func_02083b08(void *obj)
{
    *(void **) obj = (void *) &data_020e1b54;
    __cxa_vec_cleanup((char *) obj + 8, 5, 4, func_02083bac);
    func_02083c78(obj);
    func_020edb3c(obj);
    return obj;
}
