/* func_02010bac @ 0x02010bac, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct S02010BAC;

extern int func_0205cf1c(int);
extern void func_02010af4(struct S02010BAC *, int *, int);

struct S02010BAC {
    char pad_00[0x770];
    int unk_770;
};

void func_02010bac(struct S02010BAC *s, int *q, int a)
{
    int f, v;
    f = s->unk_770;
    v = func_0205cf1c(*q);
    if (v == 0x16f && f != 0xba) {
        v = 0xba;
    }
    if (v != 0x16f) {
        func_02010af4(s, &v, a);
    }
}
