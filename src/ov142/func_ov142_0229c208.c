/* func_ov142_0229c208 @ 0x0229c208, 0x84 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void *func_ov002_0220830c(void *argument0);
extern void *func_ov002_02209ccc(void *p);
extern void *func_ov002_0220a5fc(void *p);
extern void *func_ov002_0220b008(void *p);
extern void __arm __cxa_vec_ctor(void *p, int a, int b, void (*f1)(void *), void (*f2)(void *));
extern void *func_020b9cfc(void *p);
extern int **func_02070be8(void *argument0);
extern void *func_02070c08(void *argument0);
extern char data_ov142_0229c3e8;

#define VisitElement_02070c08 (void (*)(void *)) func_02070c08
#define VisitElement_02070be8 (void (*)(void *)) func_02070be8

void *func_ov142_0229c208(void)
{
    void *block = func_ov002_02207f80(0x30e0);
    if (block) {
        func_ov002_0220830c(block);
        *(void **) block = &data_ov142_0229c3e8;
        func_ov002_02209ccc((char *) block + 0xe8);
        func_ov002_0220a5fc((char *) block + 0x14c);
        func_ov002_0220b008((char *) block + 0x194);
        __cxa_vec_ctor((char *) block + 0x360, 0xe, 0x6c, VisitElement_02070c08, VisitElement_02070be8);
        {
            char *p = (char *) block + 0x948;
            char *end = (char *) block + 0x9d8;
            do {
                func_020b9cfc(p);
                p += 0x24;
            } while (p != end);
        }
    }
    return block;
}

#undef VisitElement_02070c08
#undef VisitElement_02070be8
