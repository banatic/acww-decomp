/* func_ov145_0229ace8 @ 0x0229ace8, 0x84 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov002_02207f80(int);
extern void func_ov002_0220830c(void);
extern void func_ov002_02209ccc(void *);
extern void func_ov002_0220a5fc(void *);
extern void func_ov002_0220b008(void *);
extern void func_02138d6c(void *, int, int, void (*)(void), void (*)(void));
extern void func_020b9cfc(void *);
extern char data_ov145_0229ae00;
extern void func_02070c08(void);
extern void func_02070be8(void);

void *func_ov145_0229ace8(void)
{
    void *obj;
    char *p;
    char *end;

    obj = func_ov002_02207f80(0x2508);
    if (obj != 0) {
        func_ov002_0220830c();
        *(void **) obj = &data_ov145_0229ae00;
        func_ov002_02209ccc((char *) obj + 0xC8);
        func_ov002_0220a5fc((char *) obj + 0x12C);
        func_ov002_0220b008((char *) obj + 0x174);
        func_02138d6c((char *) obj + 0x340, 0x12, 0x6C, func_02070c08, func_02070be8);
        p = (char *) obj + 0xAD8;
        end = (char *) obj + 0xB44;
        do {
            func_020b9cfc(p);
            p += 0x24;
        } while (p != end);
    }
    return obj;
}
