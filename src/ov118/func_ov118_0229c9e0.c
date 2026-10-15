/* func_ov118_0229c9e0 @ 0x0229c9e0, 0xb0 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void *func_ov002_0220830c(void *arg0);
extern void *func_020b9cfc(void *p);
extern void __cxa_vec_ctor(void *a, int b, int c, void (*callback3)(void *), void (*callback4)(void *));
extern void *func_ov002_0220a5fc(void *p);
extern void *func_ov002_02209ccc(void *p);
extern void *func_ov117_0229a2f0(void *p);
extern char data_ov118_0229cc08;
extern void *func_02070c08(void *arg0);
extern int **func_02070be8(int **arg0);
extern void func_ov118_0229a438(void *arg0);
extern void func_ov118_0229a43c(void *element);

#define DisposeElement_func_02070c08 ((void (*)(void *)) func_02070c08)

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

#define DisposeElement_func_ov118_0229a43c ((void (*)(void *)) func_ov118_0229a43c)

#define DisposeElement_func_ov118_0229a438 ((void (*)(void *)) func_ov118_0229a438)

void *func_ov118_0229c9e0(void)
{
    void *o;
    char *p;
    char *end;
    int c;

    o = func_ov002_02207f80(0x47d8);
    if (o != 0) {
        func_ov002_0220830c((void *) o);
        *(void **) o = (void *) &data_ov118_0229cc08;

        p = (char *) o + 0xb4;
        end = (char *) o + 0xfc;
        do {
            func_020b9cfc(p);
            p += 0x24;
        } while (p != end);

        __cxa_vec_ctor(end, 13, 0x6c, DisposeElement_func_02070c08, DisposeElement_func_02070be8);
        func_ov002_0220a5fc((char *) o + 0x678);
        func_ov002_02209ccc((char *) o + 0x6c0);
        func_ov117_0229a2f0((char *) o + 0x4724);

        c = 3;
        __cxa_vec_ctor((char *) o + 0x47a4, c, c, DisposeElement_func_ov118_0229a43c, DisposeElement_func_ov118_0229a438);
        __cxa_vec_ctor((char *) o + 0x47ad, 14, 3, DisposeElement_func_ov118_0229a43c, DisposeElement_func_ov118_0229a438);
    }

    return o;
}

#undef DisposeElement_func_02070c08
#undef DisposeElement_func_02070be8
#undef DisposeElement_func_ov118_0229a43c
#undef DisposeElement_func_ov118_0229a438
