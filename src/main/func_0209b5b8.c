/* func_0209b5b8 @ 0x0209b5b8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209bd80(void *);
extern int func_02003750(void *);
extern int func_02003780(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

void *func_0209b5b8(void *param)
{
    func_0209bd80(param);
    __cxa_vec_ctor((void *) ((char *) param + 12), 2, 16, (((void (*)(void *)) func_02003780)),
                   (((void (*)(void *)) func_02003750)));
    return param;
}
