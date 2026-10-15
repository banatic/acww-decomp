/* func_ov002_0220afa8 @ 0x0220afa8, 0x34 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_020edb3c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_ov002_0220b0f4(void *);
extern void *func_ov002_0220b3a4(char *arg0);
extern void *data_ov002_0220bd08;

#define DisposeElement_func_ov002_0220b3a4 ((void (*)(void *)) func_ov002_0220b3a4)

void *func_ov002_0220afa8(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bd08;
    func_ov002_0220b0f4(self + 0xfc);
    __cxa_vec_cleanup(self + 0x4, 0x2, 0x7c, DisposeElement_func_ov002_0220b3a4);
    func_020edb3c(self);
    return self;
}

#undef DisposeElement_func_ov002_0220b3a4
