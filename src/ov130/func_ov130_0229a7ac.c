/* func_ov130_0229a7ac @ 0x0229a7ac, 0x48 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void *, void *);
extern void func_02070be8(void);
extern void func_02070c08(void);
extern void func_020b9cfc(void *);

void *func_ov130_0229a7ac(void *self)
{
    char *p, *end;

    __cxa_vec_ctor((char *) self + 0x2C, 5, 0x6C, (void *) func_02070c08, (void *) func_02070be8);
    p = (char *) self + 0x248;
    end = (char *) self + 0x290;
    do {
        func_020b9cfc(p);
        p += 0x24;
    } while (p != end);
    return self;
}
