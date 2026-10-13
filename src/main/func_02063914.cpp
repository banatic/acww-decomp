/* func_02063914 @ 0x02063914, 0x284 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

struct UnkStruct_02063914 {
    virtual void v0();
    virtual int v4();
    virtual int v8();
    virtual int vc(int);
};

struct Tbl {
    u16 (*unk_00)(unsigned int);
    int (*unk_04)(u16 *);
    int (*unk_08)(u16 *);
    unsigned int count;
    int unk_10;
};

struct UnkStruct_02063914_2 {
    int a;
    int b;
};

extern "C" {
extern void func_02063e98(void *p);
extern void func_02063e8c(void *p);
extern int func_02063bb4(int a, int b);
extern int func_02063cc4(struct UnkStruct_02063914_2 *e);
extern int func_02063cc0(struct UnkStruct_02063914_2 *e);
extern int func_02063eb0(void *p, int a);
extern int func_02063f94(int a, int b, struct UnkStruct_02063914 *o);
extern int func_02063c24(int a, int b);
extern int func_02063b98(void *a, u16 *b);
extern int func_0204c260(u16 *p);
extern int func_02063c3c(u16 *a, u16 *out, int n);

extern char data_021dc7a8[];
extern struct Tbl data_020ccab0[];
}

extern "C" int func_02063914(u16 *out, unsigned int count, struct UnkStruct_02063914_2 *entries, int a4, void *a5,
                             struct UnkStruct_02063914 *a6, int a7, int a8, int *a9)
{
    int cnt;
    struct UnkStruct_02063914 *obj;
    int result;
    int v14;
    unsigned int n;
    int f1c;
    unsigned int j;
    int flag2;
    int v28;
    int found;
    unsigned int k;
    u16 tmp[2];
    int loc58[1];
    unsigned int i;
    struct UnkStruct_02063914_2 *ent;
    int kind;
    int k4;
    int r6;
    struct Tbl *tbl;
    int idx;

    result = 1;
    func_02063e98(loc58);
    obj = a6;
    if (obj == 0) {
        obj = (struct UnkStruct_02063914 *) loc58;
    }
    v14 = func_02063bb4(obj->v4(), obj->v8());
    for (i = 0; i < count; i++) {
        out[i] = 0xfff1;
    }
    if (a9 != 0) {
        *a9 = 1;
    }
    n = 0;
    while (n < count) {
        idx = obj->vc(a4);
        ent = &entries[idx];
        k4 = func_02063cc4(ent);
        r6 = func_02063eb0((char *) ((int) data_021dc7a8 + 0x173d4), k4);
        if (a8 == 1) {
            kind = func_02063f94(r6, func_02063cc0(ent), obj);
        } else {
            kind = func_02063cc0(ent);
        }
        f1c = a7;
        if (kind != 0 && kind != 1 && kind != 2 && kind != 3 && kind != 0x1d && kind != 5) {
            f1c = 0;
        }
        if (a9 != 0) {
            *a9 = kind;
        }
        tbl = &data_020ccab0[k4];
        cnt = 0;
        j = 0;
        for (; j < tbl->count; j++) {
            tmp[0] = tbl->unk_00(j);
            if (kind != tbl->unk_08(&tmp[0])) {
                continue;
            }
            if (func_02063c24(tbl->unk_04(&tmp[0]), v14) == 0) {
                continue;
            }
            if (func_02063b98(a5, &tmp[0]) != 0) {
                continue;
            }
            if (f1c != 0 && func_0204c260(&tmp[0]) != 0) {
                continue;
            }
            if (func_02063c3c(&tmp[0], out, n) != -1) {
                continue;
            }
            cnt++;
        }
        flag2 = 0;
        if (cnt == 0) {
            if (a5 != 0) {
                func_02063e8c(loc58);
                return 0;
            }
            cnt = tbl->count;
            flag2 = 1;
        }
        v28 = obj->vc(cnt);
        found = 0;
        r6 = 0;
        k = 0;
        for (; k < tbl->count; k++) {
            tmp[1] = tbl->unk_00(k);
            if (kind != tbl->unk_08(&tmp[1])) {
                continue;
            }
            if (func_02063c24(tbl->unk_04(&tmp[1]), v14) == 0) {
                continue;
            }
            if (func_02063b98(a5, &tmp[1]) != 0) {
                continue;
            }
            if (f1c != 0 && func_0204c260(&tmp[1]) != 0) {
                continue;
            }
            if (flag2 != 0) {
                if (v28 == r6) {
                    out[n++] = tmp[1];
                    found = 1;
                    break;
                }
                r6++;
            } else if (func_02063c3c(&tmp[1], out, n) == -1) {
                if (v28 == r6) {
                    out[n++] = tmp[1];
                    found = 1;
                    break;
                }
                r6++;
            }
        }
        if (found == 0) {
            out[n++] = tbl->unk_00(0);
            result = 0;
        }
    }
    func_02063e8c(loc58);
    return result;
}
