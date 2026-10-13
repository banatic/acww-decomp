/* func_02071d8c @ 0x02071d8c, 0x170 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 w[0x80];
} Head;
typedef struct {
    u16 h[6];
} UnkStruct_02071d8c;
typedef struct {
    u16 h[10];
} H10;

typedef struct {
    Head head; // 0x000
    u16 unk_200;
    UnkStruct_02071d8c unk_202;
    u16 unk_20E;
    UnkStruct_02071d8c unk_210;
    s8 unk_21C;
    u8 unk_21D;
    H10 unk_21E;
    u8 unk_232;
} Rec;

typedef struct {
    u32 a : 4;
    u32 b : 10;
    u32 c : 4;
    u32 d : 10;
    u32 e : 1;
    u32 f : 3;
} Packed;

extern int func_02071d60(int);
extern Rec *func_02071604(int, int);
extern void func_020720ac(int, int);
extern void *data_020ccf94;
extern int func_02073d90(void *);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);

int func_02071d8c(int a0, int a1, int a2, int a3, u8 flag)
{
    Packed t;
    int x, y;
    Rec *p, *q;

    x = func_02071d60(a0);
    y = func_02071d60(a2);
    if (y == 7) {
        return 0;
    }
    p = func_02071604(x, a1);
    q = func_02071604(y, a3);
    q->head = p->head;
    q->unk_200 = p->unk_200;
    q->unk_202 = p->unk_202;
    q->unk_20E = p->unk_20E;
    q->unk_210 = p->unk_210;
    q->unk_21C = p->unk_21C;
    q->unk_21D = p->unk_21D;
    q->unk_21E = p->unk_21E;
    q->unk_232 = p->unk_232;
    func_020720ac(y, a3);
    if (flag != 0 && func_02073d90(data_020ccf94) != 0) {
        void *o;
        t.a = x;
        t.b = a1;
        t.c = y;
        t.d = a3;
        t.e = 0;
        t.f = 0;
        o = data_020ccf94;
        func_02073820(o);
        func_020737f0(o, &t, 4);
        func_02073770(o, 0x15, 4);
    }
    return 1;
}
