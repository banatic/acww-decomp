/* func_02083770 @ 0x02083770, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02083ca8(void *obj, int param);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern int func_020837d0(void *);
extern int func_020837e8(void *);
extern unsigned char data_020e1ae4;

void *func_02083770(void *obj)
{
    func_02083ca8(obj, 5);
    *(unsigned int *) obj = (unsigned int) &data_020e1ae4;
    __cxa_vec_ctor((void *) ((char *) obj + 8), 5, 2, (((void (*)(void *)) func_020837e8)),
                   (((void (*)(void *)) func_020837d0)));
    return obj;
}
