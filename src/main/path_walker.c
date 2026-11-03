/* path_walker: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201272c @ 0x0201272c, 0x1c bytes, Thumb
 * func_020126d0 @ 0x020126d0, 0x5c bytes, Thumb
 * func_020126b4 @ 0x020126b4, 0x1c bytes, Thumb
 * func_020125bc @ 0x020125bc, 0xf8 bytes, Thumb
 */

typedef struct {
    int a;
    int b;
} UnkStruct_020126d0;

typedef struct {
    int pad_00;
    int v1;
    int v2;
} UnkStruct_020126d0_2;

typedef struct Elem {
    unsigned char data[0x28];
} Elem;

typedef struct Work {
    Elem *base;         // 0x00
    unsigned int count; // 0x04
    unsigned int flag;  // 0x08
} Work;

extern UnkStruct_020126d0_2 *data_021c80bc;
extern int func_020644cc(int a);
extern void func_020131dc(UnkStruct_020126d0 *out, void *param1, UnkStruct_020126d0 *computed, UnkStruct_020126d0_2 *g);
extern int func_02037d64(void *ptr, int size);
extern int func_0207cc54(unsigned char mask, int succ, int iter);
extern int func_02037e8c(void *ptr);

int func_0201272c(void *arg0, void *arg1)
{
    int val;
    int val2;
    int val3;
    int val4;

    val = *(int *) ((int) arg1 + 8);
    val2 = val >> 0x11;
    val3 = *(int *) arg1;
    val4 = val3 >> 0x11;
    if (val4 == *(int *) ((int) arg0 + 0x14) && val2 == *(int *) ((int) arg0 + 0x18)) {
        return 1;
    }
    return 0;
}

void func_020126d0(UnkStruct_020126d0 *out, void *param1)
{
    UnkStruct_020126d0_2 *g = data_021c80bc;

    out->a = 0;
    out->b = 0;
    if (g != 0) {
        char *base = (char *) g + 4;
        int v1 = *(int *) base;
        int v2 = *(int *) (base + 4);
        UnkStruct_020126d0 computed;
        UnkStruct_020126d0 local;

        computed.a = 0;
        computed.b = 0;
        if (v1 >= 3) {
            computed.a = func_020644cc(v1 - 2) + 1;
        }
        if (v2 >= 3) {
            computed.b = func_020644cc(v2 - 2) + 1;
            func_020131dc(&local, param1, &computed, g);
            out->a = local.a;
            out->b = local.b;
        }
    }
}

int func_020126b4(void *r0, void *r1)
{
    int r2, r3, r1_val;
    int *r0_ptr;

    r2 = *(int *) ((char *) r1 + 8);
    r3 = r2 >> 17;
    r1_val = *(int *) r1;
    r2 = r1_val >> 17;
    r0_ptr = (int *) ((char *) r0 + 0x14);
    if (r2 == *r0_ptr) {
        r0_ptr = (int *) ((char *) r0 + 0x18);
        if (r3 == *r0_ptr) {
            return 1;
        }
    }
    return 0;
}

void func_020125bc(unsigned int *out, unsigned int arg1, int *arg2)
{
    Work *wk = (*(Work * *) &data_021c80bc);
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
        func_020131dc((UnkStruct_020126d0 *) local, (void *) arg1, (UnkStruct_020126d0 *) (func_02037e8c(p2)), (UnkStruct_020126d0_2 *) wk);
        out[0] = local[0];
        out[1] = local[1];
    }
}
