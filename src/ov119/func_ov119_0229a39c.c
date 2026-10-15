/* func_ov119_0229a39c @ 0x0229a39c, 0x64 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov119_0229cea0;

extern void *func_ov002_0220ba0c(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_020780b8(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern int **func_02070be8(void *element);
extern void *func_ov002_02209ac8(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov119_0229a39c(void *self)
{
    *(char **) self = &data_ov119_0229cea0;
    func_ov002_0220ba0c((char *) self + 0x1efc);
    func_ov002_02209cb4((char *) self + 0xda8);
    func_020780b8((char *) self + 0xcd4);
    __cxa_vec_cleanup((char *) self + 0x4d0, 0x13, 0x6c, DisposeElement_func_02070be8);
    func_ov002_02209ac8((char *) self + 0xdc);
    func_ov002_0220826c(self);
    func_ov002_02207f6c(self);
    return self;
}

#undef DisposeElement_func_02070be8
