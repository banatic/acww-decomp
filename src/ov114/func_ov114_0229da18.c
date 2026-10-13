/* func_ov114_0229da18 @ 0x0229da18, 0x74 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229b104(void);
extern void func_ov114_0229d148(void *);
extern void func_020b9cfc(void *);
extern void func_020b9af4(void *);
extern void func_02138d6c(void *, int, int, void (*)(void), void (*)(void));
extern void func_ov002_0220a5fc(void *);
extern void func_02070be8(void);
extern void func_02070c08(void);

void *func_ov114_0229da18(void *ptr)
{
    char *p;
    char *end;

    func_ov094_0229b104();
    func_ov114_0229d148((char *) ptr + 0x808);
    func_020b9cfc((char *) ptr + 0x924);
    p = (char *) ptr + 0xe08;
    end = (char *) ptr + 0x1000;
    do {
        func_020b9af4(p);
        p += 0x38;
    } while (p != end);
    func_02138d6c((char *) ptr + 0x106c, 4, 0x6c, func_02070c08, func_02070be8);
    func_ov002_0220a5fc((char *) ptr + 0x121c);
    return ptr;
}
