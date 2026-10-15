/* func_02080d0c @ 0x02080d0c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02065f7c(void *);
extern int func_0209527c(void *, void *);
extern int func_020951bc(void *);
extern int func_020807dc(void *, void *);
extern int func_020807c0(void *, int);
extern int func_02081cd8(void *object);
extern int func_0209526c(void *);

struct LocalObj {
    unsigned char pad_00[32];
};

int func_02080d0c(void *arg0)
{
    int forwarded_value;

    int r;
    void *p;
    struct LocalObj obj;

    p = func_02065f7c((char *) arg0 + 0x634);
    if (p == 0) {
        goto fail_early;
    }
    func_0209527c(&obj, p);
    if (func_020951bc(&obj) == 0) {
        goto fail_cleanup;
    }
    r = func_020807dc(arg0, &obj);
    if ((forwarded_value = (int) func_020807c0(arg0, r)) == 0) {
        goto fail_cleanup;
    }
    if (func_02081cd8((void *) forwarded_value) == 0) {
        goto fail_cleanup;
    }
    func_0209526c(&obj);
    return r;
fail_cleanup:
    func_0209526c(&obj);
fail_early:
    return -1;
}
