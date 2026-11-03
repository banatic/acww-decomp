/* creature_draw: 12 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202ceac @ 0x0202ceac, 0x46 bytes, Thumb
 * func_0202ce24 @ 0x0202ce24, 0x88 bytes, Thumb
 * func_0202cdf8 @ 0x0202cdf8, 0x2c bytes, Thumb
 * func_0202cd78 @ 0x0202cd78, 0x80 bytes, Thumb
 * func_0202ccc0 @ 0x0202ccc0, 0xb8 bytes, Thumb
 * func_0202cca4 @ 0x0202cca4, 0x1c bytes, Thumb
 * func_0202cbfc @ 0x0202cbfc, 0xa8 bytes, Thumb
 * func_0202cbdc @ 0x0202cbdc, 0x1e bytes, Thumb
 * func_0202cb70 @ 0x0202cb70, 0x6c bytes, Thumb
 * func_0202cac4 @ 0x0202cac4, 0xac bytes, Thumb
 * func_0202c9e8 @ 0x0202c9e8, 0xdc bytes, Thumb
 * func_0202c9c0 @ 0x0202c9c0, 0x26 bytes, Thumb
 */

#include "types.h"

struct Work {
    unsigned char *entries;
    unsigned char count;
};

typedef struct Entry {
    const u8 *rec;
    u8 count;
    u8 pad_05[3];
} Entry;

struct UnkStruct_0202cdf8 {
    int unk_00;
    int unk_04;
};

typedef struct Entry_0202cd78 {
    int unk_00;
    u8 unk_04;
    u8 pad_05[3];
} Entry_0202cd78;

typedef struct Slot {
    void *p;
} Slot;

typedef struct St {
    int unk_00;
    int unk_04;
} St;

typedef struct Slot_0202c9e8 {
    Entry *e;
} Slot_0202c9e8;

extern int func_0209a478(int value);
extern int func_020644cc(int);
extern u8 data_021c1ce4[2];
extern void MI_CpuFill8(void *, int, int);
extern u8 data_021c1ce8[3];
extern int func_0204fb08(u8);
extern int func_0204fafc(u8);
extern void *func_0204fc3c(int, int);
extern unsigned char data_021c1d18[];
extern int func_0202d6e4(unsigned char *data_021c1d18, int size);
extern void MI_CpuCopy8(void *dst, const void *src, int size);
extern unsigned char data_020c8950[];
extern void func_0209e474(St *);

int func_0202ceac(int key, struct Work *p)
{
    unsigned char *e = p->entries;
    int count = 0;
    int i;

    if (e != 0 && p->count != 0) {
        for (i = 0; i < p->count; i++) {
            if (e[0] < 0x38 && e[2] != 0) {
                if (func_0209a478(e[2]) == key) {
                    count++;
                }
            }
            e += 3;
        }
    }

    return count;
}

int func_0202ce24(u16 *out1, int *out2, int key, Entry *e)
{
    const u8 *p;
    int result;
    int c;
    int k;
    int i;
    u16 v;

    p = e->rec;
    result = 0;
    if (p != 0 && e->count != 0) {
        c = func_0202ceac(key, (struct Work *) e);
        if (c > 0) {
            k = func_020644cc(c);
            for (i = 0; i < e->count; i++) {
                if (p[2] != 0 && p[0] < 0x38 && key == func_0209a478((u8) p[2])) {
                    if (k == 0) {
                        if (p[0] < 0x38) {
                            v = (u16) (p[0] + 0x12e8);
                        } else {
                            v = 0x12e8;
                        }
                        *out1 = v;
                        *out2 = p[1];
                        result = 1;
                        break;
                    }
                    k--;
                }
                p += 3;
            }
        }
    }
    return result;
}

int func_0202cdf8(int a, struct UnkStruct_0202cdf8 **b)
{
    struct UnkStruct_0202cdf8 *arr;
    int sum;
    arr = *b;
    sum = 0;
    if (arr != 0) {
        int i;
        i = 0;
        do {
            sum += func_0202ceac(a, (struct Work *) (&arr[i]));
            i++;
        } while (i < 2);
    }
    return sum;
}

int func_0202cd78(int a, int b, int key, Entry_0202cd78 **pp)
{
    Entry_0202cd78 *e;
    int result;
    int n;
    int i;
    int j;
    int k;

    e = *pp;
    result = 0;
    if (e != 0) {
        n = 0;
        MI_CpuFill8(data_021c1ce4, result, 2);
        for (i = 0; i < 2; i++) {
            if (func_0202ceac(key, (struct Work *) (&e[i])) > 0) {
                data_021c1ce4[i] = 1;
                n++;
            }
        }
        if (n > 0) {
            k = func_020644cc(n);
            for (j = 0; j < 2; j++) {
                if (data_021c1ce4[j] == 1) {
                    if (k == 0) {
                        result = func_0202ce24((u16 *) a, (int *) b, key, (Entry *) e);
                        break;
                    }
                    k--;
                }
                e += 1;
            }
        }
    }
    return result;
}

int func_0202ccc0(int a, int b, int *c, int key, Slot **pp, u8 first, u8 last8)
{
    int result;
    int last;
    int lim;
    u8 *flag;
    Slot *e;
    int n;
    int idx;
    int j;
    int i;
    int k;

    e = *pp;
    result = 0;
    if (e != 0) {
        last = 3;
        n = 0;
        MI_CpuFill8(data_021c1ce8, n, last);
        j = first;
        lim = last8;
        while (j <= lim) {
            idx = func_0204fb08((u8) j);
            flag = &data_021c1ce8[idx];
            if (data_021c1ce8[idx] == 0 && idx != last) {
                if (func_0202cdf8(key, (struct UnkStruct_0202cdf8 **) (&e[idx])) > 0) {
                    *flag = 1;
                    n++;
                }
                last = idx;
            }
            j++;
        }
        if (n > 0) {
            k = func_020644cc(n);
            for (i = 0; i < 3; i++) {
                if (data_021c1ce8[i] == 1) {
                    if (k == 0) {
                        result = func_0202cd78(a, b, key, (Entry_0202cd78 **) e);
                        *c = i;
                        break;
                    }
                    k--;
                }
                e += 1;
            }
        }
    }
    return result;
}

int func_0202cca4(int a, int b, int c, int d, int e)
{
    return func_0202ccc0(a, b, (int *) c, d, (Slot **) e, 0, 0x17);
}

int func_0202cbfc(u16 *a, int lo, int hi, int d4, u8 p5, u8 p6, u8 p7)
{
    void *tbl;
    int o1;
    int o2;
    u8 mask;
    int cnt;
    int i;
    int k;

    tbl = func_0204fc3c(d4, func_0204fafc(p5));
    if (tbl != 0) {
        mask = 0;
        cnt = hi - lo + 1;
        o1 = 0;
        o2 = 0;
        while (lo <= hi) {
            mask |= 1 << lo;
            lo++;
        }
        while (cnt > 0) {
            k = func_020644cc(cnt);
            for (i = 0; i < 5; i++) {
                if ((mask >> i) & 1) {
                    if (k == 0) {
                        if (func_0202ccc0((int) a, (int) (&o1), &o2, i, (Slot **) tbl, p6, p7) != 0) {
                            return 1;
                        }
                        mask &= ~(1 << i);
                        break;
                    }
                    k--;
                }
            }
            cnt--;
        }
    }
    return 0;
}

int func_0202cbdc(int a, int b, int c, int d, unsigned char e)
{
    return func_0202cbfc((u16 *) a, b, c, d, (unsigned char) e, 0, 23);
}

int func_0202cb70(int p0, int *p1, int p2, int p3, int p4)
{
    int res = 0;
    int i, marker;

    MI_CpuCopy8((void *) data_020c8950, data_021c1d18, 5);
    i = res;
    marker = i;

    for (; i < 5; i++) {
        int idx = func_0202d6e4(data_021c1d18, 5);
        if (idx < 0 || idx >= 5) {
            break;
        }
        if (func_0202cca4(p0, p2, p3, idx, p4) == 1) {
            *p1 = idx;
            res = 1;
            break;
        } else {
            data_021c1d18[idx] = marker;
        }
    }

    return res;
}

void func_0202cac4(u16 *p)
{
    St st;
    u8 flags[5];
    int out;
    Slot **tbl;
    Slot *e;
    unsigned int idx;
    int n;
    int i;
    int k;
    u8 t3;
    u8 t4;
    unsigned int ok;
    u16 h;

    st.unk_00 = 0;
    st.unk_04 = 0;
    n = 5;
    func_0209e474(&st);
    t4 = ((u8 *) &st)[4];
    t3 = ((u8 *) &st)[3];
    tbl = (Slot **) func_0204fc3c((u8) t4, func_0204fafc(t3));
    if (tbl != 0 && *tbl != 0) {
        idx = func_0204fb08(((u8 *) &st)[2]);
        if (idx < 3) {
            e = *tbl + idx;
            MI_CpuFill8(flags, 0, n);
            while (n > 0) {
                k = func_020644cc(n);
                for (i = 0; i < 5; i++) {
                    if (flags[i] == 0) {
                        if (k == 0) {
                            func_0202cd78((int) p, (int) (&out), i, (Entry_0202cd78 **) e);
                            flags[i] = 1;
                            break;
                        }
                        k--;
                    }
                }
                ok = 0;
                h = *p;
                if (h >= 0x12e8 && h <= 0x131f) {
                    ok = 1;
                }
                if (ok != 0) {
                    break;
                }
                n--;
            }
        }
    }
}

int func_0202c9e8(u16 *p, int j, int last, int d4, u8 p5)
{
    Slot_0202c9e8 **tbl;
    int v;
    int idx;
    Entry *e;
    const u8 *rec;
    int prev;
    int m;
    int i;
    int cnt;
    unsigned int b0;
    int t;
    unsigned int ok;
    u16 h;

    ok = 0;
    h = *p;
    if (h >= 0x12e8 && h <= 0x131f) {
        ok = 1;
    }
    if (ok > 0) {
        tbl = (Slot_0202c9e8 **) func_0204fc3c(d4, func_0204fafc(p5));
        if (tbl != 0 && *tbl != 0) {
            prev = 3;
            ok = 0;
            h = *p;
            if (h >= 0x12e8 && h <= 0x131f) {
                ok = 1;
            }
            if (ok > 0) {
                t = h - 0x12e8;
            } else {
                t = -1;
            }
            v = (u8) t;
            while (j <= last) {
                idx = func_0204fb08((u8) j);
                if (idx != prev) {
                    e = (*tbl)[idx].e;
                    if (e != 0) {
                        for (m = 0; m < 2; m++) {
                            rec = e->rec;
                            if (rec != 0) {
                                cnt = e->count;
                                if (cnt != 0) {
                                    for (i = 0; i < cnt; i++) {
                                        b0 = rec[0];
                                        if (b0 < 0x38 && b0 == v && rec[2] != 0) {
                                            return 1;
                                        }
                                        rec += 3;
                                    }
                                }
                            }
                            e += 1;
                        }
                    }
                    prev = idx;
                }
                j++;
            }
        }
    }
    return 0;
}

int func_0202c9c0(int v)
{
    switch (v) {
        case 0xc:
            return 0;
        case 1:
        case 2:
        case 4:
            return 1;
        default:
            return 2;
    }
}
