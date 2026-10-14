/* func_0203d698 @ 0x0203d698, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*)(void));
extern void func_020a79f8(void *);
extern void func_0203de30(void *);
extern void func_0203dd7c(void *);
extern void func_020a8210(void);

void *func_0203d698(void *self)
{
    __cxa_vec_cleanup((char *) self + 0x510, 0xb, 0x5c, func_020a8210);
    func_020a79f8((char *) self + 0x300);
    func_0203de30((char *) self + 0x5c);
    func_0203dd7c(self);
    return self;
}
