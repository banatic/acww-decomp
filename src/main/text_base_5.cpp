/* text_base_5: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a8bb8 @ 0x020a8bb8, 0x2c bytes, Thumb
 * func_020a8a70 @ 0x020a8a70, 0x146 bytes, Thumb
 */

class UnkStruct_020a8bb8 {
  public:
    virtual void *f0();
    virtual void *f1();
    virtual void *f2();
    virtual void *f3();
};

extern "C" void *func_020a8be4(char *a, void *v);
extern "C" void func_020a9b1c(char *a, char *b);

extern "C" {
extern int func_020a798c(char *, unsigned short);
extern const char *func_02050c20(void);
extern const char *func_02050c28(void);
extern unsigned char *strcpy(char *, const char *);
extern int strlen(const char *);
}

struct NStr {
    virtual void v0();
    virtual void v1();
    virtual unsigned int len();
    virtual char *buf();
};

struct WStr {
    virtual void v0();
    virtual void v1();
    virtual int len();
    virtual unsigned short *buf();
};

extern "C" void *func_020a8bb8(char *a, char *b)
{
    void *ret = func_020a8be4(a, ((UnkStruct_020a8bb8 *) b)->f3());
    func_020a9b1c(a + 8, b + 8);
    return ret;
}

extern "C" int func_020a8a70(NStr *dst, WStr *src, int p2, int p3)
{
    char tmp[8];
    int n;
    unsigned short *sp;
    char *dp;
    unsigned int cap;
    unsigned int k;
    int over;
    int done;
    int i;
    char *q;
    unsigned int m;
    unsigned int j;
    char c;

    n = src->len();
    sp = src->buf();
    dp = dst->buf();
    cap = dst->len();
    k = 0;
    over = 0;
    done = 0;
    i = 0;
    while (i < n) {
        q = dp + k;
        m = func_020a798c(tmp, *sp);
        if (k + m > cap) {
            over = 1;
        }
        if (over == 0) {
            c = tmp[0];
            if (c == 0 && tmp[1] == 0) {
                done = 1;
                if (p3 != 0) {
                    strcpy(tmp, func_02050c20());
                    m = strlen(tmp);
                    if (k + m > cap) {
                        over = 1;
                    }
                }
            } else if (p2 != 0 && c == 0xa && tmp[1] == 0) {
                strcpy(tmp, func_02050c28());
                m = strlen(tmp);
                if (k + m > cap) {
                    over = 1;
                }
            }
            if (over == 0) {
                for (j = 0; j < m; j++) {
                    q[j] = tmp[j];
                }
            }
        }
        if (over != 0) {
            break;
        }
        k += m;
        if (done != 0) {
            break;
        }
        i++;
        sp++;
    }
    if (over == 0 && k < cap) {
        done = 1;
        while (k < cap) {
            dp[k] = 0;
            k++;
        }
    }
    if (done == 0) {
        *(dp + cap - 1) = 0;
    }
    func_020a9b1c((char *) ((char *) dst + 8), (char *) ((char *) src + 4));
    if (over == 0 && done != 0) {
        return 1;
    }
    return 0;
}
