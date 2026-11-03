/* villager_part_block: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209ae20 @ 0x0209ae20, 0x50 bytes, Thumb
 * func_0209ade4 @ 0x0209ade4, 0x3c bytes, Thumb
 * func_0209adb0 @ 0x0209adb0, 0x34 bytes, Thumb
 */

extern void *func_0209b594(void *);
extern void *func_0209b5b8(void *);
extern int func_02003780(void *);
extern int func_02003750(void *);
extern void func_0209bd80(void *);
extern void *func_0209af44(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_0209af2c(void *);
extern void func_0209bd7c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_0209b56c(void *);
extern void func_0209ac30(void *);
extern void func_0209b23c(void *);
extern void func_0209af04(void *);

void *func_0209ae20(void *obj)
{
    __cxa_vec_ctor((void *) (obj), 2, 0x30, (((void (*)(void *)) func_0209b5b8)), (((void (*)(void *)) func_0209b594)));
    __cxa_vec_ctor((void *) ((char *) obj + 0x60), 3, 0x10, (((void (*)(void *)) func_02003780)),
                   (((void (*)(void *)) func_02003750)));
    func_0209bd80((char *) obj + 0x94);
    func_0209af44((char *) obj + 0xa4);
    return obj;
}

void *func_0209ade4(void *self)
{
    func_0209af2c((char *) self + 0xa4);
    func_0209bd7c((char *) self + 0x94);
    __cxa_vec_cleanup((void *) ((char *) self + 0x60), 3, 0x10, (((void (*)(void *)) func_02003750)));
    __cxa_vec_cleanup((void *) (self), 2, 0x30, (((void (*)(void *)) func_0209b594)));
    return self;
}

void func_0209adb0(void *arg0)
{
    int i;
    void *p;

    for (i = 0; i < 2; i++) {
        p = (char *) arg0 + i * 0x30;
        func_0209b56c(p);
    }

    func_0209ac30(arg0);
    func_0209b23c((char *) arg0 + 0x94);
    func_0209af04((char *) arg0 + 0xa4);
}
