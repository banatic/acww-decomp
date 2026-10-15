/* func_ov140_0229b268 @ 0x0229b268, 0x78 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(int);
extern void *func_ov002_0220830c(void *argument0);
extern void *func_ov139_02299b54(char *);
extern void *func_ov002_02209ccc(char *);
extern void *func_ov002_0220b008(char *);
extern void *func_020b9cfc(char *);
extern int **func_02070be8(void *argument0);
extern void *func_02070c08(void *argument0);
extern void __cxa_vec_ctor(char *, int, int, void (*)(void *), void (*)(void *));
extern char data_ov140_0229b404;

#define VisitElement_02070c08 (void (*)(void *)) func_02070c08
#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

void *func_ov140_0229b268(void)
{
    void *r4 = func_ov002_02207f80(0x1c00);
    if (r4) {
        func_ov002_0220830c(r4);
        *(void **) r4 = &data_ov140_0229b404;
        func_ov139_02299b54((char *) r4 + 0x8e8);
        func_ov002_02209ccc((char *) r4 + 0x128c);
        func_ov002_0220b008((char *) r4 + 0x12f0);
        func_020b9cfc((char *) r4 + 0x14bc);
        __cxa_vec_ctor((char *) r4 + 0x1abc, 3, 0x6c, VisitElement_02070c08, VisitElement_02070be8);
    }
    return r4;
}

#undef VisitElement_02070c08
#undef VisitElement_02070be8
