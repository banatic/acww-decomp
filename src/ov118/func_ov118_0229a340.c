/* func_ov118_0229a340 @ 0x0229a340, 0x78 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov118_0229cc08;
extern void __cxa_vec_cleanup(void *a, int b, int c, void (*callback3)(void *));
extern void func_ov117_0229a2ec(void *a);
extern void *func_ov002_02209cb4(void *a);
extern void *func_ov002_0220a5e4(void *a);
extern void *func_ov002_0220826c(void *a);
extern void func_ov118_0229a438(void *element);
extern int **func_02070be8(int **arg0);

#define DisposeElement_func_ov118_0229a438 ((void (*)(void *)) func_ov118_0229a438)

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov118_0229a340(void *self)
{
    *(int *) self = (int) &data_ov118_0229cc08;
    __cxa_vec_cleanup((char *) self + 0x47ad, 14, 3, DisposeElement_func_ov118_0229a438);
    __cxa_vec_cleanup((char *) self + 0x47a4, 3, 3, DisposeElement_func_ov118_0229a438);
    func_ov117_0229a2ec((char *) self + 0x4724);
    func_ov002_02209cb4((char *) self + 0x6c0);
    func_ov002_0220a5e4((char *) self + 0x678);
    __cxa_vec_cleanup((char *) self + 0xfc, 13, 0x6c, DisposeElement_func_02070be8);
    func_ov002_0220826c(self);
    return self;
}

#undef DisposeElement_func_ov118_0229a438
#undef DisposeElement_func_02070be8
