/* func_02074b44 @ 0x02074b44, 0x1e0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x6d];
    u8 unk_6D;
    u8 pad_6E[2];
    int unk_70;
    u8 unk_74;
} UnkStruct_02074b44;

extern void func_0207718c(void);
extern int func_02077afc(int a, int b);
extern void func_02073d64(UnkStruct_02074b44 *g, int a);
extern void func_02073bf0(UnkStruct_02074b44 *g, int a);
extern void func_02073878(UnkStruct_02074b44 *g, int a);
extern void func_02073760(UnkStruct_02074b44 *g, int a);
extern void func_020736ac(UnkStruct_02074b44 *g, int a);
extern void func_02073588(UnkStruct_02074b44 *g, int a);
extern void func_020734c0(UnkStruct_02074b44 *g, int a);
extern void func_0207341c(UnkStruct_02074b44 *g, int a);
extern void func_020733b8(UnkStruct_02074b44 *g, int a);
extern void func_02073044(void);
extern void func_020ece54(int a, int b, int c, long long d, int f, void *g, void *h);
extern void func_020730c8(void);
extern void func_020ecce4(int a, void *f);
extern void *func_02073144(UnkStruct_02074b44 *g);
extern void *func_02073138(UnkStruct_02074b44 *g);
extern void MI_CpuFill8(void *dst, int v, int n);
extern void *func_020984e8(void);
extern void *func_02099658(void *h);
extern void *func_02077d00(void *p);
extern void *func_02077c3c(void *p);
extern void *func_02077d68(void *p);
extern void MI_CpuCopy8(const void *src, void *dst, int n);
extern void *func_02099870(void *h);
extern void *func_020950a8(void *p);
extern void *func_020642a4(void *p);
extern void *func_02099664(void *h);
extern void *func_02077bcc(void *p);
extern void func_02073100(void);
extern void func_020ecba8(int a, void *f, void *g, void *p, void *q);
extern void func_020732b4(UnkStruct_02074b44 *g, int a);

extern void func_02077ae8(void);
extern void func_02075050(void);
extern void func_02099e78(void);

extern UnkStruct_02074b44 *data_020ccf94;
extern u8 data_021dc7a8[];

void func_02074b44(int a0, int a1, int a2)
{
    UnkStruct_02074b44 *g;
    UnkStruct_02074b44 *g2;
    void *arr;
    void *rec;
    void *h;
    u8 *q;
    int i;

    g = data_020ccf94;
    g->unk_74 = 1;
    func_0207718c();
    g->unk_70 = func_02077afc(g->unk_6D, 4);
    func_02073d64(g, func_02077afc(0x3000, 4));
    func_02073bf0(g, func_02077afc(0x9000, 4));
    func_02073878(g, func_02077afc(0x91a, 4));
    func_02073760(g, func_02077afc(0x91a, 4));
    func_020736ac(g, func_02077afc(0x91a, 4));
    func_02073588(g, func_02077afc(0x91a, 4));
    func_020734c0(g, func_02077afc(0x91a, 4));
    func_0207341c(g, func_02077afc(0xc00, 4));
    func_020733b8(g, func_02077afc(0xc00, 4));
    func_02073044();
    func_020ece54(0x41444d4b, 0x00c0001b, 1, 0x004fe752, a1, (void *) func_02077afc, (void *) func_02077ae8);
    if ((u8) (a0 + 0xff) <= 1) {
        func_020730c8();
        func_020ecce4(a0, (void *) func_02075050);
    } else {
        g2 = data_020ccf94;
        arr = func_02073144(g2);
        rec = func_02073138(g2);
        MI_CpuFill8(arr, 0, 0x5e0);
        MI_CpuFill8(rec, 0, 0x60);
        h = func_020984e8();
        q = func_02077d00(func_02099658(h));
        for (i = 0; i < 0x20; i++) {
            MI_CpuCopy8(func_02077d68(func_02077c3c(q)), (char *) arr + i * 12, 12);
            q += 0x24;
        }
        MI_CpuCopy8(func_020950a8(func_02099870(h)), rec, 12);
        MI_CpuCopy8(func_020642a4((char *) data_021dc7a8 + 2), (char *) rec + 0x10, 12);
        MI_CpuCopy8(func_02077bcc(func_02099664(h)), (char *) rec + 0x20, 0x40);
        func_02073100();
        func_020ecba8(a0, (void *) func_02075050, (void *) func_02099e78, rec, arr);
    }
    func_020732b4(g, a2);
}
