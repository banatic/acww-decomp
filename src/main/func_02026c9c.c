/* func_02026c9c @ 0x02026c9c, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02026c9c_4 {
    const void *text;
    u8 unk_04;
    u8 unk_05, unk_06, unk_07;
} UnkStruct_02026c9c_4;
typedef struct UnkStruct_02026c9c {
    u8 pad_00[0x830];
    void *unk_830;
} UnkStruct_02026c9c;

typedef struct UnkStruct_02026c9c_2 {
    u8 pad_00[0x100];
    UnkStruct_02026c9c *unk_100;
    u8 unk_104[0x1e];
    u8 unk_122;
    u8 unk_123;
    u16 unk_124;
    u8 pad_126[0x3a];
    void *unk_160;
    u8 pad_164[0x3c];
    int unk_1A0;
} UnkStruct_02026c9c_2;

typedef struct UnkStruct_02026c9c_5 {
    u8 *ptr;
    u8 unk_04;
} UnkStruct_02026c9c_5;
typedef struct UnkStruct_02026c9c_3 {
    u16 a;
    u16 b;
    unsigned int c;
} UnkStruct_02026c9c_3;

extern const UnkStruct_02026c9c_4 data_020c8d98;

extern u8 *func_0209b408(void *a);
extern void func_0202d5e4(UnkStruct_02026c9c_3 *l, int n);
extern int func_0205be38(void);
extern int func_0202b510(int a);
extern void func_02027170(u16 *p, int a);
extern unsigned int func_0208150c(void *a);
extern void *func_020036e8(unsigned char *);
extern int func_0202da38(UnkStruct_02026c9c_2 *p, u8 *buf, u8 *flag, int size, void *a, const void *text, int b, int c, int d);

void func_02026c9c(UnkStruct_02026c9c_2 *p, UnkStruct_02026c9c_5 *out)
{
    UnkStruct_02026c9c_3 l;
    u8 kind;

    kind = *func_0209b408(p->unk_160);
    p->unk_124 = 0xfff1;
    if (kind == 2) {
        func_0202d5e4(&l, 0);
        p->unk_124 = l.a;
    }
    if (p->unk_124 == 0xfff1) {
        p->unk_1A0 = func_0205be38() * 4 + 0x1f4;
        p->unk_1A0 = func_0202b510(p->unk_1A0);
        func_02027170(&l.b, p->unk_1A0);
        p->unk_124 = l.b;
    }
    func_0202da38(p, p->unk_104, &p->unk_122, 0x1e, func_020036e8((unsigned char *) func_0208150c(p->unk_100->unk_830)),
                  data_020c8d98.text, data_020c8d98.unk_04, 0, 0);
    out->ptr = p->unk_104;
    out->unk_04 = p->unk_122;
}
