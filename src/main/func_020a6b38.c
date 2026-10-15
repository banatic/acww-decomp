/* func_020a6b38 @ 0x020a6b38, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_020a77c8(void *);
extern void func_020a76e4(void *);
extern void func_020a7718(void *);
extern void func_020a7754(void *);

void *func_020a6b38(void *self)
{
    __cxa_vec_cleanup((void *) ((char *) self + 0x3c), 4, 8, (void (*)(void *)) func_020a77c8);
    __cxa_vec_cleanup((void *) ((char *) self + 0x2c), 4, 4, (void (*)(void *)) func_020a76e4);
    __cxa_vec_cleanup((void *) ((char *) self + 0xc), 4, 8, (void (*)(void *)) func_020a7718);
    __cxa_vec_cleanup((void *) (self), 4, 3, (void (*)(void *)) func_020a7754);
    return self;
}
