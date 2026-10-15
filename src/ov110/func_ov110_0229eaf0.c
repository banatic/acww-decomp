/* func_ov110_0229eaf0 @ 0x0229eaf0, 0xc0 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void *func_ov002_0220830c(void *self);
extern void *func_020b9af4(void *p);
extern void *func_ov094_0229b000(void *p);
extern void func_ov094_0229bc3c(void *p);
extern void *func_ov094_0229a2ec(void *p);
extern void *func_ov002_02207e40(void *p);
extern void func_ov002_02209e44(void *p);
extern void *func_ov002_02209ccc(void *p);
extern void *func_ov002_02209b14(void *p);
extern void *func_ov002_0220ba24(void *p);
extern int **func_02070be8(void *argument0);
extern void *func_02070c08(void *argument0);
extern void __cxa_vec_ctor(void *p, int a, int b, void (*c)(void *), void (*d)(void *));
extern int data_ov110_0229ecb8;

#define VisitElement_02070c08 (void (*)(void *)) func_02070c08
#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

void *func_ov110_0229eaf0(void)
{
    char *self;
    char *p;
    char *end;

    self = func_ov002_02207f80(0x292c);
    if (self == 0) {
        goto done;
    }

    func_ov002_0220830c(self);
    *(void **) self = (void *) &data_ov110_0229ecb8;

    p = self + 0x100;
    end = self + 0x138;
    do {
        func_020b9af4(p);
        p += 0x38;
    } while (p != end);

    func_ov094_0229b000(end);
    func_ov094_0229bc3c(self + 0xb98);
    func_ov094_0229a2ec(self + 0xbc0);
    func_ov002_02207e40(self + 0x21f8);
    func_ov002_02209e44(self + 0x22c8);
    func_ov002_02209ccc(self + 0x22e0);
    func_ov002_02209b14(self + 0x2344);
    func_ov002_0220ba24(self + 0x2738);
    __cxa_vec_ctor(self + 0x2854, 2, 0x6c, VisitElement_02070c08, VisitElement_02070be8);

done:
    return self;
}

#undef VisitElement_02070c08
#undef VisitElement_02070be8
