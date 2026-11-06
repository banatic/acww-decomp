/* session_link_3: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02074af8 @ 0x02074af8, 0x4c bytes, Thumb
 * func_020749c4 @ 0x020749c4, 0x134 bytes, Thumb
 * func_02074958 @ 0x02074958, 0x6c bytes, Thumb
 * func_02074944 @ 0x02074944, 0x12 bytes, Thumb
 * func_02074904 @ 0x02074904, 0x40 bytes, Thumb
 */

typedef struct UnkStruct_02074af8 {
    unsigned char pad_00[0x74];
    unsigned char unk_74;
} UnkStruct_02074af8;

typedef struct UnkStruct_020749c4 {
    unsigned char pad_00[0x70];
    int unk_70;
    unsigned char unk_74;
} UnkStruct_020749c4;

typedef struct {
    char pad_00[0x74];
    unsigned char flag_0x74;
} UnkStruct_02074958;

struct Object {
    char pad_00[0x64];
    int unk_64;
};

extern UnkStruct_02074af8 *data_020ccf94;
extern unsigned int func_02073044(void);
extern int func_02077afc(int size, int type);
extern void func_02077ae8(int r);
extern void func_020ece54(int code, int a, int b, long long size, int n, int (*f1)(int, int), void (*f2)(int));
extern void *data_021c9b30;
extern unsigned int func_020e9a3c(void *t, unsigned int f);
extern int func_020ec4a8(void);
extern void func_020b8d6c(void);
extern int func_020733c4(UnkStruct_020749c4 *p);
extern void func_020733b8(UnkStruct_020749c4 *p, int v);
extern int func_02073424(UnkStruct_020749c4 *p);
extern void func_0207341c(UnkStruct_020749c4 *p, int v);
extern int func_020734c8(UnkStruct_020749c4 *p);
extern void func_020734c0(UnkStruct_020749c4 *p, int v);
extern int func_02073590(UnkStruct_020749c4 *p);
extern void func_02073588(UnkStruct_020749c4 *p, int v);
extern int func_020736b4(UnkStruct_020749c4 *p);
extern void func_020736ac(UnkStruct_020749c4 *p, int v);
extern int func_02073768(UnkStruct_020749c4 *p);
extern void func_02073760(UnkStruct_020749c4 *p, int v);
extern int func_02073884(UnkStruct_020749c4 *p);
extern void func_02073878(UnkStruct_020749c4 *p, int v);
extern int func_02073c04(UnkStruct_020749c4 *p, int a, int b);
extern void func_02073bf0(UnkStruct_020749c4 *p, int v);
extern int func_02073d28(UnkStruct_020749c4 *p, int a);
extern void func_02073d64(UnkStruct_020749c4 *p, int v);
extern int func_020738e4(UnkStruct_020749c4 *p);
extern void func_020738e0(UnkStruct_020749c4 *p, int v);
extern void func_02073f00(UnkStruct_020749c4 *p);
extern void func_020ecf1c(void);
extern void func_0205cb4c(void);
extern struct Object;
extern int func_02073dd4(struct Object *p, int field);
extern int func_02073d70(struct Object *p);
extern void func_020734d0(struct Object *p);
extern void func_0207342c(struct Object *p);
extern void func_020739d0(struct Object *p);

void func_02074af8(void)
{
    data_020ccf94->unk_74 = 1;
    func_02073044();
    func_020ece54(0x41444d4b, 0x00c0001c, 1, 0x004fe752, 2, func_02077afc, func_02077ae8);
}

int func_020749c4(void)
{
    void *h;
    unsigned int old;
    int ret;
    UnkStruct_020749c4 *p;

    ret = 1;
    if ((*(UnkStruct_020749c4 **) &data_020ccf94)->unk_74 != 0) {
        h = data_021c9b30;
        old = func_020e9a3c(h, 0x8000);
        ((unsigned int) func_020e9a3c(h, old | 0x2000), func_02073044());
        if (func_020ec4a8() == 0) {
            func_020b8d6c();
            ret = 0;
        }
        func_020e9a3c(h, old);
        p = (*(UnkStruct_020749c4 **) &data_020ccf94);
        func_02077ae8(func_020733c4(p));
        func_020733b8(p, 0);
        func_02077ae8(func_02073424(p));
        func_0207341c(p, 0);
        func_02077ae8(func_020734c8(p));
        func_020734c0(p, 0);
        func_02077ae8(func_02073590(p));
        func_02073588(p, 0);
        func_02077ae8(func_020736b4(p));
        func_020736ac(p, 0);
        func_02077ae8(func_02073768(p));
        func_02073760(p, 0);
        func_02077ae8(func_02073884(p));
        func_02073878(p, 0);
        func_02077ae8(func_02073c04(p, 4, 0));
        func_02073bf0(p, 0);
        func_02077ae8(func_02073d28(p, 4));
        func_02073d64(p, 0);
        func_02077ae8(p->unk_70);
        p->unk_70 = 0;
        func_02077ae8(func_020738e4(p));
        func_020738e0(p, 0);
        func_02073f00(p);
        p->unk_74 = 0;
    }
    return ret;
}

/* FAKEMATCH: the no-op 64-bit mask keeps val in r5 and ret in r4; without it the registers swap */
void func_02074958(void)
{
    int ret;
    int val;
    UnkStruct_02074958 *p;
    if ((*(UnkStruct_02074958 **) &data_020ccf94)->flag_0x74 == 0) {
        return;
    }
    val = (*(int *) &data_021c9b30);
    ret = (int) func_020e9a3c((void *) val, 0x8000);
    ret = ret & 0xFFFFFFFFFFFFFFFFu;
    ((unsigned int) (int) func_020e9a3c((void *) val, ret | 0x2000), func_02073044());
    if (func_020ec4a8() == 0) {
        func_020b8d6c();
    }
    func_020e9a3c((void *) val, ret);
    p = (*(UnkStruct_02074958 **) &data_020ccf94);
    func_02073f00((UnkStruct_020749c4 *) p);
    p->flag_0x74 = 0;
}

void func_02074944(void)
{
    func_020ecf1c();
    func_0205cb4c();
}

void func_02074904(int flag)
{
    struct Object *p;
    if (flag != 0) {
        return;
    }
    p = (*(struct Object **) &data_020ccf94);
    if (func_02073dd4(p, p->unk_64) == 0) {
        return;
    }
    if (func_02073d70(p) == 0) {
        return;
    }
    p = (*(struct Object **) &data_020ccf94);
    func_020734d0(p);
    func_0207342c(p);
    func_020739d0(p);
}
