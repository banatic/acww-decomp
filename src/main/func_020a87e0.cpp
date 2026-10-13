/* func_020a87e0 @ 0x020a87e0, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,p
 */

extern "C" {
extern int func_020a7984(void *, const unsigned char *);
extern void func_020a9b1c(void *, void *);
}
struct Str {
    virtual void v0();
    virtual void v1();
    virtual unsigned int len();
    virtual unsigned char *buf();
};
extern "C" int func_020a87e0(Str *dst, Str *src)
{
    unsigned char *sp;
    unsigned short *dp;
    unsigned int slen, dlen;
    unsigned int i, j;
    int n;
    int ok;
    unsigned short tmp;
    sp = src->buf();
    slen = src->len();
    j = 0;
    dp = (unsigned short *) dst->buf();
    dlen = dst->len();
    i = j;
    ok = 1;
    while (j < slen && i < dlen) {
        n = func_020a7984(&tmp, sp);
        *dp = tmp;
        dp++;
        i++;
        sp += n;
        j += n;
    }
    if (i >= dlen && *sp != 0) {
        ok = 0;
    }
    goto cond;
pad:
    *dp = 0;
    i++;
    dp++;
cond:
    if (i < dlen) {
        goto pad;
    }
    func_020a9b1c((char *) dst + 4, (char *) src + 8);
    return ok;
}
