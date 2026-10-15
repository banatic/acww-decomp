/* func_ov002_02209ac8 @ 0x02209ac8, 0x4c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_ov002_022087bc(void *);
extern void *func_ov002_0220b0f4(void *);
extern void *func_ov002_0220b464(void *);
extern void *func_ov002_02209bf0(void *arg0);
extern void *data_ov002_0220bb98;

#define DisposeElement_func_ov002_02209bf0 ((void (*)(void *)) func_ov002_02209bf0)

void *func_ov002_02209ac8(char *self)
{
    // DECLS
    // ENDDECLS
    *(void **) (self) = &data_ov002_0220bb98;
    func_ov002_022087bc(self + 0x3b0);
    func_ov002_0220b0f4(self + 0x2e4);
    func_ov002_0220b464(self + 0x26c);
    __cxa_vec_cleanup(self + 0x28, 0x5, 0x74, DisposeElement_func_ov002_02209bf0);
    return self;
}

#undef DisposeElement_func_ov002_02209bf0
