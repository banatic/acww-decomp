/* func_0209a9a8 @ 0x0209a9a8, 0xd8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short unk_00;
    unsigned char m[12];
    unsigned char pad_0E;
    unsigned char unk_0F;
} Rec;

extern int func_02065ec0(void *b);
extern void *func_0209ad9c(void *a, int k);
extern void *func_0209b4d4(void *);
extern int func_0209bc40(unsigned char *);
extern int func_02065f64(void *b);
extern void *func_02003760(Rec *r, int v);
extern int func_02003704(Rec *r);
extern int func_02003750(Rec *r);
extern Rec *func_0209b4cc(void *h, int k);
extern int memcmp(const void *a, const void *b, unsigned int n);
extern unsigned int func_0209bba0(void *c);
extern void func_0209bb90(void *c, int k);

int func_0209a9a8(void *a, void *b)
{
    Rec tmp;
    void *h;
    void *c;
    int v;
    Rec *p;

    if (b == 0) {
        goto fail;
    }
    if (func_02065ec0(b) == 0) {
        goto fail;
    }
    h = func_0209ad9c(a, 0);
    c = func_0209b4d4((void *) h);
    if (func_0209bc40(c) != 0xf) {
        goto fail;
    }
    v = func_02065f64(b);
    if (v != 0) {
        func_02003760(&tmp, v);
        if (func_02003704(&tmp) != 0) {
            p = func_0209b4cc(h, 1);
            if (p->unk_00 == tmp.unk_00 && memcmp(p->m, tmp.m, 0xc) == 0 && p->unk_0F == tmp.unk_0F) {
                if (func_0209bba0(c) < 2) {
                    func_0209bb90(c, 2);
                    func_02003750(&tmp);
                    return 1;
                }
                goto cleanup;
            }
        }
        if (func_0209bba0(c) != 0) {
            goto cleanup;
        }
        func_0209bb90(c, 1);
        func_02003750(&tmp);
        return 1;
    cleanup:
        func_02003750(&tmp);
        goto fail;
    } else {
        if (func_0209bba0(c) == 0) {
            func_0209bb90(c, 1);
            return 1;
        }
    }
fail:
    return 0;
}
