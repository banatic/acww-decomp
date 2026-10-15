/* func_ov112_0229ef2c @ 0x0229ef2c, 0x90 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov112_022a20d0;
extern void *func_02078040(void *);
extern void *func_020780b8(void *);
extern void *func_ov002_02209cb4(void *);
extern void *func_ov002_0220afdc(void *);
extern void *func_ov002_0220a5e4(void *);
extern int **func_02070be8(void *element);
extern void *func_ov002_0220ba0c(void *);
extern void *func_ov002_0220826c(void *);
extern void func_ov002_02207f6c(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov112_0229ef2c(void *obj)
{
    *(void **) obj = &data_ov112_022a20d0;
    func_02078040((char *) obj + 0x4580);
    func_020780b8((char *) obj + 0x44ac);
    func_ov002_02209cb4((char *) obj + 0x4448);
    func_ov002_0220afdc((char *) obj + 0x427c);
    func_ov002_0220a5e4((char *) obj + 0x4234);
    __cxa_vec_cleanup((char *) obj + 0x3fac, 6, 0x6c, DisposeElement_func_02070be8);
    __cxa_vec_cleanup((char *) obj + 0x26d4, 2, 0x6c, DisposeElement_func_02070be8);
    func_ov002_0220ba0c((char *) obj + 0x244);
    func_ov002_0220826c(obj);
    func_ov002_02207f6c(obj);
    return obj;
}

#undef DisposeElement_func_02070be8
