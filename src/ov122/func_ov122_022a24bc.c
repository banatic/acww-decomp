/* func_ov122_022a24bc @ 0x022a24bc, 0xc4 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int size);
extern void func_ov002_0220830c(void);
extern void func_020b9cfc(void *p);
extern void __cxa_vec_ctor(void *p, int a, int b, void (*cb1)(void), void (*cb2)(void));
extern void func_0206e388(void *p);
extern void func_ov002_0220a5fc(void *p);
extern void func_ov002_02209ccc(void *p);
extern void func_0206da98(void *p);
extern void func_02065cb0(void *p);
extern void func_ov002_02209b14(void *p);
extern void func_ov002_0220b008(void *p);
extern void func_ov002_0220ba24(void *p);
extern void func_02070be8(void);
extern void func_02070c08(void);

extern unsigned char data_ov122_022a2738[];

void *func_ov122_022a24bc(void)
{
    void *p;
    char *base;
    char *q;
    char *end;

    p = func_ov002_02207f80(0x4980);
    if (p == 0) {
        goto ret;
    }

    func_ov002_0220830c();
    *(void **) p = (void *) data_ov122_022a2738;

    base = (char *) p + 0xc0;
    q = base + 0x2308;
    end = base + 0x2350;
    do {
        func_020b9cfc(q);
        q += 0x24;
    } while (q != end);

    __cxa_vec_ctor(end, 2, 0x6c, func_02070c08, func_02070be8);

    func_0206e388((char *) p + 0x3ce8);
    func_ov002_0220a5fc((char *) p + 0x4010);
    func_ov002_02209ccc((char *) p + 0x4058);
    func_0206da98((char *) p + 0x40bc);
    func_02065cb0((char *) p + 0x4150);
    func_ov002_02209b14((char *) p + 0x42b0);
    func_ov002_0220b008((char *) p + 0x4698);
    func_ov002_0220ba24((char *) p + 0x4864);

ret:
    return p;
}
