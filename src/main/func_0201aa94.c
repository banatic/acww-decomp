/* func_0201aa94 @ 0x0201aa94, 0xda bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x1a];
    short unk_1A;
    short unk_1C;
    char pad_1E[4];
    short unk_22;
    short unk_24;
    char pad_26[4];
    char flag;
} UnkStruct_0201aa94;

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
} SomeB;

extern int func_0201ac10(UnkStruct_0201aa94 *a, void *p1, void *p2, short s);
extern int func_0201a814(UnkStruct_0201aa94 *a, int x);
extern int func_0201ad8c(UnkStruct_0201aa94 *a, void *buf);
extern int func_0201ab94(UnkStruct_0201aa94 *a, int d, void *buf, int zero);
extern int func_0201abac(UnkStruct_0201aa94 *a, int x);
extern int func_020ea9e4(void *p1, void *p2);
extern int func_020e8870(short *target, int val, short other);

void func_0201aa94(UnkStruct_0201aa94 *a, SomeB *b, void *c, int d, int e, unsigned char f)
{
    char *c_p = (char *) c + 0x5c;
    char *b_p = (char *) b + 0x5c;
    char buffer[16];
    int r4 = 0;
    int r7 = 0;
    int r6;

    a->flag = 0;
    if (c_p != 0) {
        r6 = func_020ea9e4(c_p, b_p);
        if (e != 0) {
            if (r6 < 0) {
                r6 = -r6;
            }
            if (r6 >= e) {
                goto label1;
            }
        }
        r6 = func_0201ac10(a, c_p, b_p, b->unk_8E);
        if (f != 0) {
            if (func_0201a814(a, r6) == 0) {
                goto label1;
            }
        }
        if (func_0201ad8c(a, buffer) != 0) {
            r4 = func_0201ab94(a, d, buffer, 0);
        }
        r7 = func_0201abac(a, r6);
        a->flag = 1;
    }
label1:
    if (a->unk_22 != r7) {
        func_020e8870(&a->unk_22, r7, a->unk_24);
    }
    if (a->unk_1A != r4) {
        func_020e8870(&a->unk_1A, r4, a->unk_1C);
    }
    if (!(a->unk_22 == r7 && a->unk_1A == r4)) {
        a->flag = 0;
    }
}
