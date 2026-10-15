/* func_0200d900 @ 0x0200d900, 0x13c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[4];
    u8 unk_04;
} UnkStruct_0200d900;
typedef struct {
    u8 a;
    u8 b;
} TB;

typedef struct {
    u8 pad_00[0x234];
    u8 unk_234;
    u8 pad_235[0x388 - 0x235];
    u8 unk_388;
    u8 unk_389;
    u8 pad_38A[0x700 - 0x38a];
    u8 unk_700;
    u8 unk_701;
    u8 pad_702[0x710 - 0x702];
    u8 unk_710;
    u8 pad_711[0x73c - 0x711];
    u8 unk_73C;
    u8 pad_73D[0x7d4 - 0x73d];
    UnkStruct_0200d900 q;
    u8 pad_7D9[0x800 - 0x7d9];
    int unk_800;
    u8 pad_804[0xc8c - 0x804];
    int unk_C8C;
    u8 pad_C90[0xc94 - 0xc90];
    int unk_C94;
} UnkStruct_0200d900_2;

extern u8 data_020c75c0[];
extern TB data_020c75e8[];
extern void func_020058b4(void *state);

extern int func_0205cfe8(u8 *p);
extern int func_0205cfd4(u8 *p);
extern void func_020554b0(u8 *p, int a);
extern int func_020961d0(int a);
extern void func_0205f750(u8 *p, int a);
extern int func_0205f73c(u8 *p);
extern int func_020548cc(u8 *p, int a);
extern int func_02055478(u8 *p, int a);
extern void func_02010c34(UnkStruct_0200d900_2 *s);
extern void func_0205ccc4(u8 *p, int a);
extern void func_020109fc(UnkStruct_0200d900_2 *s, int a, int b, int c);
extern void func_02055050(u8 *p);
extern void func_02055de0(u8 *p, int callback, int a, int b, UnkStruct_0200d900_2 *s, int c);
extern void func_02056730(u8 *p);

int func_0200d900(UnkStruct_0200d900_2 *s)
{
    int ret;
    UnkStruct_0200d900 *q;
    int k;
    unsigned int ok1;
    unsigned int ok2;
    int a;
    int t;

    ret = 0;
    q = &s->q;
    if (q->unk_04 == 0) {
        a = func_0205cfe8(&s->unk_389);
        if (s->unk_C94 == 2) {
            ok1 = 1;
        } else {
            ok1 = ret;
        }
        ok2 = (s->unk_C8C == 2);
        if (a != 0 && ok1 != 0 && ok2 != 0) {
            t = func_0205cfd4(&s->unk_389);
            func_020554b0(&s->unk_234, t);
            t = func_020961d0(s->unk_800);
            func_0205f750(&s->unk_388, data_020c75c0[t]);
            t = func_0205f73c(&s->unk_388);
            func_020548cc(&s->unk_234, t);
            t = func_0205f73c(&s->unk_388);
            func_02055478(&s->unk_234, t);
            func_02010c34(s);
            k = func_020961d0(s->unk_800);
            func_0205ccc4(&s->unk_700, data_020c75e8[k].a);
            func_0205ccc4(&s->unk_701, data_020c75e8[k].b);
            func_020109fc(s, 0, 0, 0);
            func_02055050(&s->unk_234);
            func_02055de0(&s->unk_234, (int) func_020058b4, 6, 1, s, 0);
            func_02056730(&s->unk_710);
            func_02056730(&s->unk_73C);
            ret = 1;
            q->unk_04 = q->unk_04 + 1;
        }
    }
    return ret;
}
