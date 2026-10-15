/* func_ov133_0229c70c @ 0x0229c70c, 0x84 bytes, Thumb, module ov133
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(int size);
extern void *func_ov002_0220830c(void *arg0);
extern void __cxa_vec_ctor(void *base, int count, int size, void (*callback3)(void *), void (*callback4)(void *));
extern void *func_ov002_02209ccc(void *p);
extern void *func_ov002_0220b008(void *p);
extern void *func_020b9cfc(void *p);
extern void *func_ov002_0220ba24(void *p);
extern void *func_02070c08(void *p);
extern int **func_02070be8(void *p);
extern void *data_ov133_0229c908;

#define DisposeElement_func_02070c08 ((void (*)(void *)) func_02070c08)

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov133_0229c70c(void)
{
    char *p = (char *) func_ov002_02207f80(0x14b0);

    if (p) {
        char *q;
        char *end;

        func_ov002_0220830c((void *) p);
        *(void **) p = &data_ov133_0229c908;
        __cxa_vec_ctor(p + 0xb0, 1, 0x6c, DisposeElement_func_02070c08, DisposeElement_func_02070be8);
        func_ov002_02209ccc(p + 0x11c);
        func_ov002_0220b008(p + 0x180);
        q = p + 0x34c;
        end = p + 0x394;
        do {
            func_020b9cfc(q);
            q += 0x24;
        } while (q != end);
        func_ov002_0220ba24(p + 0x1394);
    }
    return p;
}

#undef DisposeElement_func_02070c08
#undef DisposeElement_func_02070be8
