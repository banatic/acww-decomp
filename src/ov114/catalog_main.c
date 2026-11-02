/* catalog_main: 4 functions, module ov114
 * mwccarm 1.2/base -O4,s
 * func_ov114_0229da18 @ 0x0229da18, 0x74 bytes, Thumb
 * func_ov114_0229d9d8 @ 0x0229d9d8, 0x40 bytes, Thumb
 * func_ov114_0229d8d0 @ 0x0229d8d0, 0x108 bytes, Thumb
 * func_ov114_0229d8ac @ 0x0229d8ac, 0x24 bytes, Thumb
 */

extern void func_ov094_0229b104(char **arg0);
extern void *func_ov114_0229d148(void *);
extern void *func_020b9cfc(void *);
extern void *func_020b9af4(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void *func_ov002_0220a5fc(void *);
extern int **func_02070be8(void *element);
extern void *func_02070c08(void *element);
extern void *func_ov002_0220a5e4(void *p);
extern void __cxa_vec_cleanup(void *p, int a, int b, void (*callback3)(void *));
extern void *func_ov114_0229d130(void *p);
extern void func_ov094_0229b0f8(void *p);
extern unsigned char func_02002d50(unsigned int direction);
extern void func_ov094_0229b0d4(void *);
extern void func_ov114_0229c9dc(void *);
extern void func_ov114_0229c1e4(void *);
extern void func_ov002_0220a580(void *);
extern void func_020a8c1c(void *);
extern void func_020b9ccc(void *);
extern void func_ov114_0229cde4(void *);
extern void func_ov114_0229cda0(void *);

#define DisposeElement_func_02070c08 ((void (*)(void *)) func_02070c08)

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov114_0229da18(void *ptr)
{
    char *p;
    char *end;

    func_ov094_0229b104((char **) ptr);
    func_ov114_0229d148((char *) ptr + 0x808);
    func_020b9cfc((char *) ptr + 0x924);
    p = (char *) ptr + 0xe08;
    end = (char *) ptr + 0x1000;
    do {
        func_020b9af4(p);
        p += 0x38;
    } while (p != end);
    __cxa_vec_ctor((char *) ptr + 0x106c, 4, 0x6c, DisposeElement_func_02070c08, DisposeElement_func_02070be8);
    func_ov002_0220a5fc((char *) ptr + 0x121c);
    return ptr;
}

#undef DisposeElement_func_02070c08
#undef DisposeElement_func_02070be8

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov114_0229d9d8(void *arg)
{
    func_ov002_0220a5e4((char *) arg + 0x121c);
    __cxa_vec_cleanup((char *) arg + 0x106c, 4, 0x6c, DisposeElement_func_02070be8);
    func_ov114_0229d130((char *) arg + 0x808);
    func_ov094_0229b0f8(arg);
    return arg;
}

#undef DisposeElement_func_02070be8

void func_ov114_0229d8d0(unsigned char *obj, unsigned char p1, unsigned char p2, unsigned char p3, unsigned char p4)
{
    *(unsigned short *) (obj + 0x12ac) = 0;
    *(obj + 0x12b1) = p1;
    *(obj + 0x12b2) = p2;
    *(obj + 0x12b3) = p3;
    *(unsigned int *) (obj + 0x12a4) = func_02002d50(p2);
    *(unsigned int *) (obj + 0x12a8) = func_02002d50(p3);
    *(obj + 0x12b7) = p4;
    func_ov094_0229b0d4(obj);
    func_ov114_0229c9dc(obj);
    switch (p4) {
        case 0:
            *(unsigned int *) (obj + 0x1294) = 0x38;
            *(obj + 0x12bd) = 7;
            break;
        case 1:
            *(unsigned int *) (obj + 0x1294) = 0x38;
            *(obj + 0x12bd) = 8;
            break;
        default:
            *(unsigned int *) (obj + 0x1294) = 0x38;
            *(obj + 0x12bd) = 0;
            break;
    }
    func_ov114_0229c1e4(obj);
    *(obj + 0x12bc) = 0x10;
    *(unsigned int *) (obj + 0x1298) = (*(unsigned int *) (obj + 0x1294) - 8) * 0x1b;
    *(unsigned int *) (obj + 0x1280) = 0;
    func_ov002_0220a580(obj + 0x121c);
    *(obj + 0x12af) = 0;
    *(obj + 0x12ae) = *(obj + 0x12af);
    func_020a8c1c(obj + 0x808);
    *(obj + 0x12bb) = 4;
}

void func_ov114_0229d8ac(void *self)
{
    func_020b9ccc((char *) self + 0x924);
    func_ov114_0229cde4(self);
    func_ov114_0229cda0(self);
}
