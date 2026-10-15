/* func_02081398 @ 0x02081398, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02065f7c(void *);
extern int func_020951bc(void *);
extern int func_0209527c(void *, void *);
extern int memcmp(const void *, const void *, unsigned int);
extern int func_0209518c(void *, void *);
extern int func_020807a8(void *, void *);
extern int func_02081cd8(void *object);
extern int func_0209526c(void *);

struct LocalObj {
    unsigned short unk_00;
    unsigned char unk_02[12];
    unsigned char pad_0E[18]; // pad to 32 bytes total
};

int func_02081398(void *arg0, struct LocalObj *arg1)
{
    int forwarded_value;

    void *p;
    struct LocalObj obj;

    p = func_02065f7c((char *) arg0 + 0x634);
    if (func_020951bc(arg1) == 0) {
        goto fail_early;
    }
    if (p == 0) {
        goto fail_early;
    }

    func_0209527c(&obj, p);

    if (arg1->unk_00 != obj.unk_00) {
        goto fail_cleanup;
    }
    if (memcmp(&arg1->unk_02, &obj.unk_02, 12) != 0) {
        goto fail_cleanup;
    }
    if (func_0209518c(arg1, &obj) == 0) {
        goto fail_cleanup;
    }
    if ((forwarded_value = (int) func_020807a8(arg0, arg1)) == 0) {
        goto fail_cleanup;
    }
    if (func_02081cd8((void *) forwarded_value) == 0) {
        goto fail_cleanup;
    }

    func_0209526c(&obj);
    return 1;

fail_cleanup:
    func_0209526c(&obj);
fail_early:
    return 0;
}
