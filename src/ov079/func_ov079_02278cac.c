/* func_ov079_02278cac @ 0x02278cac, 0x50 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int a;
    unsigned int b;
} PairT;

typedef struct {
    char pad_00[0xb4];
    PairT p1;
    PairT p2;
    unsigned short flag;
    char pad_C6[2];
    int some;
} ObjT;

extern PairT data_0213dd98;
extern void func_0201612c(void *p);

void func_ov079_02278cac(ObjT *s)
{
    PairT tmp;
    func_0201612c(s);
    s->some = -1;
    s->flag = 0xfff1;
    tmp = data_0213dd98;
    s->p1 = tmp;
    s->p2 = tmp;
}
