/* func_020839a4 @ 0x020839a4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e1aac;
extern void __arm __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_02083c78(void *self);
extern void func_020edb3c(void *self);
extern void *func_02083a50(void *);

void *func_020839a4(void *self)
{
    *(void **) self = (void *) &data_020e1aac;
    __cxa_vec_cleanup((void *) ((char *) self + 8), 8, 8, (((void (*)(void *)) func_02083a50)));
    func_02083c78(self);
    func_020edb3c(self);
    return self;
}
