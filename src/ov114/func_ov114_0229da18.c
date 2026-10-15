/* func_ov114_0229da18 @ 0x0229da18, 0x74 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229b104(char **arg0);
extern void *func_ov114_0229d148(void *);
extern void *func_020b9cfc(void *);
extern void *func_020b9af4(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*callback3)(void *), void (*callback4)(void *));
extern void *func_ov002_0220a5fc(void *);
extern int **func_02070be8(void *element);
extern void *func_02070c08(void *element);

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
