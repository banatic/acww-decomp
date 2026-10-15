/* func_020a6b88 @ 0x020a6b88, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_020a6998(void *obj);
extern void func_020a7754(void *);
extern void *func_020a7758(void *);
extern void func_020a7718(void *);
extern int func_020a771c(void *);
extern void func_020a76e4(void *);
extern void *func_020a76e8(void *);
extern void func_020a77c8(void *);
extern int func_020a77cc(void *);

void *func_020a6b88(void *obj)
{
    __cxa_vec_ctor((void *) (obj), 4, 3, (((void (*)(void *)) func_020a7758)), (void (*)(void *)) func_020a7754);
    __cxa_vec_ctor((void *) ((char *) obj + 0xc), 4, 8, (((void (*)(void *)) func_020a771c)),
                   (void (*)(void *)) func_020a7718);
    __cxa_vec_ctor((void *) ((char *) obj + 0x2c), 4, 4, (((void (*)(void *)) func_020a76e8)),
                   (void (*)(void *)) func_020a76e4);
    __cxa_vec_ctor((void *) ((char *) obj + 0x3c), 4, 8, (((void (*)(void *)) func_020a77cc)),
                   (void (*)(void *)) func_020a77c8);
    func_020a6998(obj);
    return obj;
}
