/* func_ov113_0229aae4 @ 0x0229aae4, 0x80 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void func_ov002_0220830c(void *p);
extern void func_020b9cfc(void *p);
extern void __cxa_vec_ctor(void *ptr, int a, int b, void (*c)(void), void (*d)(void));
extern void func_02070be8(void);
extern void func_02070c08(void);
extern void func_ov002_02209c78(void *p);

typedef struct {
    void *vtable;
} UnkStruct_0229aae4;

extern UnkStruct_0229aae4 data_ov113_0229ac00;

void *func_ov113_0229aae4(void)
{
    char *p;
    char *q;
    char *end;

    p = (char *) func_ov002_02207f80(0x2b84);
    if (p != 0) {
        func_ov002_0220830c(p);
        ((UnkStruct_0229aae4 *) p)->vtable = &data_ov113_0229ac00;
        q = p + 0x26a0;
        end = p + 0x26e8;
        do {
            func_020b9cfc(q);
            q += 0x24;
        } while (q != end);
        __cxa_vec_ctor(end, 4, 0x6c, func_02070c08, func_02070be8);
        __cxa_vec_ctor(p + 0x2898, 6, 0x6c, func_02070c08, func_02070be8);
        func_ov002_02209c78(p + 0x2b20);
    }
    return p;
}
