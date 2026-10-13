/* func_020125bc @ 0x020125bc, 0xf8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Elem {
    unsigned char data[0x28];
} Elem;

typedef struct Work {
    Elem *base;         // 0x00
    unsigned int count; // 0x04
    unsigned int flag;  // 0x08
} Work;

extern Work *data_021c80bc;

extern int func_02037d64(void *ptr, int size);
extern int func_0207cc54(unsigned char mask, int succ, int iter);
extern int func_02037e8c(void *ptr);
extern void func_020131dc(unsigned int *out, unsigned int arg1, int val, void *wk);

void func_020125bc(unsigned int *out, unsigned int arg1, int *arg2)
{
    Work *wk = data_021c80bc;
    unsigned char mask = 0;
    int succ, iter, cnt;
    int a, b, r4;
    void *p;
    void *p2;
    int one;
    unsigned int local[2];
    int ret;
    int *pc;

    out[0] = 0;
    out[1] = 0;
    if (wk == (Work *) 0) {
        return;
    }

    pc = (int *) &wk->count;
    cnt = *pc;
    succ = 0;
    iter = 0;

    if (pc[1] <= 4 || cnt > 8) {
        // skip
    } else {
        a = arg2[0] >> 17;
        b = arg2[2] >> 17;
        r4 = 1;
        one = 1;

        while (r4 < cnt - 1) {
            if (r4 == a && b == 4) {
                // nothing
            } else {
                if (r4 < wk->count && wk->flag > 4 && wk->base != (Elem *) 0) {
                    p = (void *) ((unsigned char *) wk->base + (r4 + wk->count * 4) * 0x28);
                } else {
                    p = (void *) 0;
                }
                if (p != (void *) 0 && func_02037d64(p, 8) != 0) {
                    mask = (unsigned char) (mask | (one << (r4 - 1)));
                    succ++;
                }
            }
            iter++;
            r4++;
        }
    }

    ret = func_0207cc54(mask, succ, iter);
    if ((unsigned int) ret >= iter) {
        return;
    }

    if (ret + 1 < wk->count && wk->flag > 4 && wk->base != (Elem *) 0) {
        p2 = (void *) ((unsigned char *) wk->base + (ret + 1 + wk->count * 4) * 0x28);
    } else {
        p2 = (void *) 0;
    }
    if (p2 != (void *) 0) {
        func_020131dc(local, arg1, func_02037e8c(p2), wk);
        out[0] = local[0];
        out[1] = local[1];
    }
}
