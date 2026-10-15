/* func_ov048_02262958 @ 0x02262958, 0x8c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020682e0(int);
extern int func_0208602c(void);
extern int func_020860cc(int);
extern void *func_020961a8(int);
extern void func_0204f818(int *, int *, int *);
extern void func_02087e88(int, int);
extern void func_02087e80(int, int);
extern void func_0203acd8(void);
extern void func_020a18f4(void);
extern int func_020b5e10(void);
extern int func_020b63f4(int, int, int *, unsigned int, int, int, int);
extern void func_ov048_022635f4(void *, int);

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_02262958;

typedef struct {
    char pad_00[0x5c];
    UnkStruct_02262958 sub;
    char pad_68[0x26];
    short sfield;
} PStruct;

typedef struct {
    char pad_00[4];
    int unk_04;
} EarlyStruct;

int func_ov048_02262958(void *obj)
{
    int a, b;
    int r4;
    int r6;
    int sub[3];
    PStruct *p;
    EarlyStruct *e;
    UnkStruct_02262958 *sp;

    e = func_020682e0(0);
    if (e->unk_04 == 5) {
        r6 = func_020860cc((int) func_0208602c());
        p = func_020961a8(4);
        sp = &p->sub;
        sub[0] = p->sub.unk_00;
        sub[1] = sp->unk_04;
        sub[2] = sp->unk_08;
        r4 = p->sfield;
        a = 0;
        b = 0;
        func_0204f818(&a, &b, sub);
        func_02087e88(r6, 1);
        func_02087e80(r6, ((PStruct *) obj)->sfield);
        func_0203acd8();
        func_020a18f4();
        func_020b63f4(func_020b5e10(), 0xc, sub, 0x00800000, r4, 2, 2);
        func_ov048_022635f4(obj, 3);
    }
    return 1;
}
