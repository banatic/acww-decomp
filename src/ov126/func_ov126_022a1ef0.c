/* func_ov126_022a1ef0 @ 0x022a1ef0, 0xb8 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void *func_ov002_0220830c(void *argument0);
extern void *func_ov124_0229f460(void *p);
extern void *func_020b9cfc(void *p);
extern void __cxa_vec_ctor(void *p, int a, int b, void *cb1, void *cb2);
extern void *func_ov002_0220b008(void *p);
extern void *func_ov002_02209ccc(void *p);
extern void *func_02070c08(void *p);
extern void *func_020707d0(void *p);
extern void *func_ov002_0220ba24(void *p);
extern int **func_02070be8(void *argument0);
extern unsigned char data_ov126_022a20c8[];

#define VisitElement_02070c08 (void *) func_02070c08
#define VisitElement_02070be8 (void *) (int **(*) (void *) ) func_02070be8

void *func_ov126_022a1ef0(void)
{
    void *obj = func_ov002_02207f80(0x4288);
    if (obj) {
        char *base;
        char *p;
        char *end;

        func_ov002_0220830c(obj);
        *(void **) obj = data_ov126_022a20c8;
        func_ov124_0229f460((char *) obj + 0xb0);

        base = (char *) obj + 0x19c;
        p = base + 0x2308;
        end = base + 0x2350;
        do {
            func_020b9cfc(p);
            p += 0x24;
        } while (p != end);

        __cxa_vec_ctor(end, 2, 0x6c, VisitElement_02070c08, VisitElement_02070be8);
        func_ov002_0220b008((char *) obj + 0x3dc4);
        func_ov002_02209ccc((char *) obj + 0x3f90);
        func_02070c08((char *) obj + 0x3ff4);
        func_02070c08((char *) obj + 0x4060);
        func_020707d0((char *) obj + 0x40cc);
        func_ov002_0220ba24((char *) obj + 0x412c);
    }
    return obj;
}

#undef VisitElement_02070c08
#undef VisitElement_02070be8
