/* func_ov132_0229b888 @ 0x0229b888, 0x7c bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

extern char *func_ov002_02207f80(int);
extern void *func_ov002_0220830c(void *arg0);
extern void *func_ov002_02209ccc(void *);
extern void *func_ov002_0220b008(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern int **func_02070be8(void *element);
extern void *func_02070c08(void *element);
extern void *func_020b9cfc(void *);
extern void *func_ov002_0220ba24(void *);
extern int data_ov132_0229b990;

#define DisposeElement_func_02070c08 ((void (*)(void *)) func_02070c08)

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

char *func_ov132_0229b888(void)
{
    char *p;

    p = func_ov002_02207f80(0x1508);
    if (p != 0) {
        char *it;
        char *end;

        func_ov002_0220830c((void *) p);
        *(void **) p = (void *) &data_ov132_0229b990;
        func_ov002_02209ccc(p + 0x94);
        func_ov002_0220b008(p + 0xf8);
        __cxa_vec_ctor(p + 0x2c4, 2, 0x6c, DisposeElement_func_02070c08, DisposeElement_func_02070be8);

        it = p + 0x39c;
        end = p + 0x3e4;
        do {
            func_020b9cfc(it);
            it += 0x24;
        } while (it != end);
        func_ov002_0220ba24(end);
    }
    return p;
}

#undef DisposeElement_func_02070c08
#undef DisposeElement_func_02070be8
