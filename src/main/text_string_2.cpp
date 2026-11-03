/* text_string_2: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02051a78 @ 0x02051a78, 0x1a bytes, Thumb
 * func_02051984 @ 0x02051984, 0xf4 bytes, Thumb
 * func_0205195c @ 0x0205195c, 0x26 bytes, Thumb
 */

class UnkStruct_02051a78 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
};

extern "C" int func_02051a94(void *dst, int value);

extern "C" {
extern int func_02050c78(char *, unsigned short);
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

class UnkStruct_0205195c {
  public:
    virtual void v0();
    virtual void v1();
    virtual int getCount();
    virtual void *getBuffer();
};

extern "C" void MI_CpuFill8(void *dest, int ch, unsigned int n);

extern "C" void func_02051a78(void *dst, UnkStruct_02051a78 *obj)
{
    func_02051a94(dst, obj->v3());
}

extern "C" int func_02051984(NStr *dst, WStr *src)
{
    char tmp[4];
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
        m = func_02050c78(tmp, *sp);
        if (k + m <= cap) {
            if (m == 1) {
                *q = tmp[0];
                if (tmp[0] == 0) {
                    done = 1;
                }
            } else if (m == 2) {
                *q = tmp[0];
                q[1] = tmp[1];
                if (tmp[0] == 0 && tmp[1] == 0) {
                    done = 1;
                }
            }
        } else {
            over = 1;
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
    if (over == 0 && done != 0) {
        return 1;
    }
    return 0;
}

extern "C" void func_0205195c(UnkStruct_0205195c *obj)
{
    int size = obj->getCount() * 2;
    MI_CpuFill8(obj->getBuffer(), 0, size);
}
