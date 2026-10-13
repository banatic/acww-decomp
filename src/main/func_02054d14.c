/* func_02054d14 @ 0x02054d14, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02056b18(void *p, void *q);
extern void MTX_Identity33_(void *p);

void func_02054d14(void *p, void *q)
{
    void *r0;
    void *r5 = p;
    void *r4 = q;
    void *r1;
    void *r2;
    int flags;

    r0 = (char *) r4 + 0xb4;
    r0 = *(void **) r0;
    flags = *(int *) r0;
    if (flags & 4) {
        *(int *) ((char *) r0 + 0x4c) = 0;
        *(int *) ((char *) r0 + 0x50) = 0;
        *(int *) ((char *) r0 + 0x54) = 0;
    }
    flags = *(int *) r0;
    if (flags & 2) {
        MTX_Identity33_((char *) r0 + 0x28);
    }
    r0 = (char *) r5 + 0xf0;
    r0 = *(void **) r0;
    if (r0 != 0) {
        func_02056b18((char *) r5 + 0xb8, r4);
    }
}
