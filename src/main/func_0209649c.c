/* func_0209649c @ 0x0209649c, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);
extern void *func_020b65c4(void);
extern void func_02077a54(void *, void *, int);
extern int func_02096518(void *, int, int);
extern void func_020778e0(short *, short);
extern int func_0207762c(void *);
extern void MI_CpuCopy8(void *, void *, int);

void func_0209649c(void *a, void *b)
{
    struct {
        int f0;
        struct {
            char c0;
            unsigned char c1;
            short s;
        } sub;
        char buf[8];
    } local;

    void *p = func_02096718(4);

    if (p) {
        void *q = func_020b65c4();
        func_02077a54(&local.sub, q, 0);

        if (func_02096518(&local, -1, 4)) {
            local.sub.c1 = (unsigned char) (local.f0 + 1);
        }

        func_020778e0(&local.sub.s, *(short *) ((char *) p + 0xc84));
        MI_CpuCopy8((char *) p + 0x8f0, local.buf, 8);
    } else {
        local.sub.c1 = 0x94u;
    }

    MI_CpuCopy8(&local.sub, a, func_0207762c(b));
}
