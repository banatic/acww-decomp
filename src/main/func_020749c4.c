/* func_020749c4 @ 0x020749c4, 0x134 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020749c4 {
    unsigned char pad_00[0x70];
    int unk_70;
    unsigned char unk_74;
} UnkStruct_020749c4;

extern UnkStruct_020749c4 *data_020ccf94;
extern void *data_021c9b30;

extern unsigned int func_020e9a3c(void *t, unsigned int f);
extern unsigned int func_02073044(void);
extern int func_020ec4a8(void);
extern void func_020b8d6c(void);
extern void func_02077ae8(int r);

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

int func_020749c4(void)
{
    void *h;
    unsigned int old;
    int ret;
    UnkStruct_020749c4 *p;

    ret = 1;
    if (data_020ccf94->unk_74 != 0) {
        h = data_021c9b30;
        old = func_020e9a3c(h, 0x8000);
        ((unsigned int) func_020e9a3c(h, old | 0x2000), func_02073044());
        if (func_020ec4a8() == 0) {
            func_020b8d6c();
            ret = 0;
        }
        func_020e9a3c(h, old);
        p = data_020ccf94;
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
