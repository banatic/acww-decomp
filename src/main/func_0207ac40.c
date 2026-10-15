/* func_0207ac40 @ 0x0207ac40, 0x7a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0207ac40 {
    char pad_00[0x20];
    int unk_20;
    unsigned short unk_24;
} UnkStruct_0207ac40;

struct St {
    char data[20];
};

extern UnkStruct_0207ac40 *func_0207cec0(int a, int);
extern void *func_0208150c(UnkStruct_0207ac40 *p);
extern int func_02003704(void *p);
extern UnkStruct_0207ac40 *func_0207f270(UnkStruct_0207ac40 *p);
extern void func_0205ba64(void *p);
extern int func_0205b868(void *p, int q, unsigned short *r, int *s, int *t, int *u);
extern void func_0205ba60(void *p);

void func_0207ac40(int param1, int param2)
{
    unsigned short s;
    int a;
    int b;
    int c;
    struct St st;
    UnkStruct_0207ac40 *r5;

    r5 = func_0207cec0(param1, param2);
    if (r5 == 0) {
        return;
    }

    if (func_02003704(func_0208150c(r5)) == 0) {
        return;
    }

    a = 5;
    b = 0;
    c = 0;
    s = 0;

    if (func_02003704(func_0208150c(r5)) == 0) {
        return;
    }

    r5 = func_0207f270(r5);
    if (r5 == 0) {
        return;
    }

    func_0205ba64(&st);
    s = 0;

    r5->unk_20 = func_0205b868(&st, param2, &s, &a, &b, &c);
    r5->unk_24 = s;

    func_0205ba60(&st);
}
