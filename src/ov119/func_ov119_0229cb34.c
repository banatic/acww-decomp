/* func_ov119_0229cb34 @ 0x0229cb34, 0x8c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(int size);
extern void *func_ov002_0220830c(void *arg0);
extern void *func_ov002_02209b14(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void *func_020780d0(void *);
extern void *func_ov002_02209ccc(void *);
extern void *func_020b9cfc(void *);
extern void *func_ov002_0220ba24(void *);
extern char data_ov119_0229cea0[];
extern void *func_02070c08(void *element);
extern int **func_02070be8(void *element);

#define DisposeElement_func_02070c08 ((void (*)(void *)) func_02070c08)

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov119_0229cb34(void)
{
    char *p;
    p = (char *) func_ov002_02207f80(0x2018);
    if (p == 0) {
        goto out;
    }

    func_ov002_0220830c((void *) p);
    *(void **) p = data_ov119_0229cea0;
    func_ov002_02209b14(p + 0xdc);
    __cxa_vec_ctor(p + 0x4d0, 0x13, 0x6c, DisposeElement_func_02070c08, DisposeElement_func_02070be8);
    func_020780d0(p + 0xcd4);
    func_ov002_02209ccc(p + 0xda8);

    {
        char *q = p + 0x1e90;
        char *end = p + 0x1efc;
        do {
            func_020b9cfc(q);
            q += 0x24;
        } while (q != end);
        func_ov002_0220ba24(end);
    }

out:
    return (void *) p;
}

#undef DisposeElement_func_02070c08
#undef DisposeElement_func_02070be8
