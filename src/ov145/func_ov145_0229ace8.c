/* func_ov145_0229ace8 @ 0x0229ace8, 0x84 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(int);
extern void *func_ov002_0220830c(void *argument0);
extern void *func_ov002_02209ccc(void *);
extern void *func_ov002_0220a5fc(void *);
extern void *func_ov002_0220b008(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *func_020b9cfc(void *);
extern char data_ov145_0229ae00;
extern void *func_02070c08(void *argument0);
extern int **func_02070be8(void *argument0);

#define VisitElement_02070c08 (void (*)(void *)) func_02070c08
#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

void *func_ov145_0229ace8(void)
{
    void *obj;
    char *p;
    char *end;

    obj = func_ov002_02207f80(0x2508);
    if (obj != 0) {
        func_ov002_0220830c(obj);
        *(void **) obj = &data_ov145_0229ae00;
        func_ov002_02209ccc((char *) obj + 0xC8);
        func_ov002_0220a5fc((char *) obj + 0x12C);
        func_ov002_0220b008((char *) obj + 0x174);
        __cxa_vec_ctor((char *) obj + 0x340, 0x12, 0x6C, VisitElement_02070c08, VisitElement_02070be8);
        p = (char *) obj + 0xAD8;
        end = (char *) obj + 0xB44;
        do {
            func_020b9cfc(p);
            p += 0x24;
        } while (p != end);
    }
    return obj;
}

#undef VisitElement_02070c08
#undef VisitElement_02070be8
