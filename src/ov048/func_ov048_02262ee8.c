/* func_ov048_02262ee8 @ 0x02262ee8, 0x70 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O1,s
 */

extern void *func_020984e8(void);
extern int func_020883cc(void);
extern void *func_02099688(void *);
extern unsigned short *func_020882ec(void *);
extern int func_02064294(void *);
extern int memcmp(const void *, const void *, int);
extern void func_02088284(void);
extern int func_0208829c(void *);
extern void func_02098ff8(void *, int);
extern const unsigned short data_021dc7aa[];

int func_ov048_02262ee8(void)
{
    void *a, *b;
    const unsigned short *tbl;
    unsigned short *p;

    a = func_020984e8();
    if (func_020883cc() != 0) {
        b = func_02099688(a);
        if (func_02064294(func_020882ec(b)) != 0) {
            tbl = data_021dc7aa;
            p = func_020882ec(b);
            if (*p == tbl[0] && memcmp(p + 1, tbl + 1, 0xc) == 0) {
                goto skip;
            }
        }
        func_02099688(func_020984e8());
        func_02088284();
    skip:
        if (func_0208829c(b) != 0) {
            func_02098ff8(a, 0x36);
            return 1;
        }
    }
    return 0;
}
