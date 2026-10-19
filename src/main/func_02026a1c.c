/* func_02026a1c @ 0x02026a1c, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern void *func_02099734(void *);
extern void func_02098a24(void *, int, int);
extern int func_02098eb8(void *);
extern int func_02098f0c(void *, void *, int, int);
extern void *func_020996ac(void *);
extern int func_0203cd2c(void *, void *, int, int);
extern int func_020154b4(void *, void *, int, int, int);

void func_02026a1c(void *obj)
{
    void *h, *ctx;
    unsigned int ok;
    unsigned short v;
    int rc;

    h = func_020984e8();
    ctx = func_02099734(h);
    ok = 0;
    v = *(unsigned short *) ((char *) obj + 0x124);
    if (v >= 0x1492 && v <= 0x14fd) {
        ok = 1;
    }
    if (ok > 0) {
        func_02098a24(ctx, *(int *) ((char *) obj + 0x1a0), 1);
    } else if (v != 0xfff1) {
        rc = func_02098eb8(ctx);
        if (rc != -1) {
            func_02098f0c(ctx, (char *) obj + 0x124, rc, 0);
            func_0203cd2c(func_020996ac(h), (char *) obj + 0x124, 0, 1);
        }
    }
    func_020154b4(obj, (char *) obj + 0x124, 0, 5, 0);
}
