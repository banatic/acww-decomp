/* func_ov111_022a0e08 @ 0x022a0e08, 0x9c bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(unsigned int);
extern void func_ov002_0220830c(void *);
extern void func_020b9cfc(void *);
extern void func_0203a404(void *);
extern void func_020a88ec(void *);
extern void func_ov002_02209ccc(void *);
extern void func_ov002_0220ba24(void *);
extern void func_02138d6c(void *, int, int, void (*)(void), void (*)(void));
extern void func_02070c08(void);
extern void func_02070be8(void);
extern unsigned char data_ov111_022a1008[];
extern unsigned char data_ov111_022a0ff0[];

void *func_ov111_022a0e08(void)
{
    void *p = func_ov002_02207f80(0x3ed8);
    if (p != 0) {
        char *r1, *r4, *r6;

        func_ov002_0220830c(p);
        *(unsigned char **) p = data_ov111_022a1008;

        r1 = (char *) p + 0xac;
        r4 = r1 + 0x2308;
        r6 = r1 + 0x2350;
        do {
            func_020b9cfc(r4);
            r4 += 0x24;
        } while (r4 != r6);

        func_02138d6c(r6, 2, 0x6c, &func_02070c08, &func_02070be8);
        func_0203a404((char *) p + 0x3cd4);
        func_020a88ec((char *) p + 0x3d08);
        *(unsigned char **) ((char *) p + 0x3d08) = data_ov111_022a0ff0;
        func_ov002_02209ccc((char *) p + 0x3d38);
        func_ov002_0220ba24((char *) p + 0x3d9c);
    }
    return p;
}
