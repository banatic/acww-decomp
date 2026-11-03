/* villager_talk_replies_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02020e00 @ 0x02020e00, 0x64 bytes, Thumb
 * func_02020d98 @ 0x02020d98, 0x68 bytes, Thumb
 */

typedef struct UnkStruct_02020e00 {
    unsigned char pad_00[0x830];
    int val;
} UnkStruct_02020e00;

typedef struct UnkStruct_02020e00_2 {
    unsigned char pad_00[0x100];
    UnkStruct_02020e00 *p;
    unsigned char data[0x1e];
    unsigned char b;
} UnkStruct_02020e00_2;

typedef struct UnkStruct_02020e00_3 {
    void *ptr;
    unsigned char b;
} UnkStruct_02020e00_3;

typedef struct {
    int a;
    unsigned char b;
} UnkStruct_02020e00_4;

typedef struct {
    int a, b;
} PairStruct;

typedef struct {
    char buffer[32];
    volatile unsigned char pair[2];
} FrameLocals;

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern UnkStruct_02020e00_4 data_020c8a88;
extern void func_0201cf90(void *, void *, int, int, int, int);
extern void func_0201cec8(void *, void *);
extern void func_0202da74(void *, PairStruct);
extern void func_02068388(int, int);
extern const PairStruct data_020d9280;
extern unsigned char data_021c21cc[];
extern unsigned char data_021c21e4[];

void func_02020e00(UnkStruct_02020e00_2 *r5, UnkStruct_02020e00_3 *r4)
{
    int a, b, c, d, e;
    a = func_020036e8(func_0208150c(r5->p->val));
    b = data_020c8a88.a;
    c = data_020c8a88.b;
    d = 0;
    e = 0;
    func_0202da38(r5, r5->data, &r5->b, 0x1e, a, b, c, d, e);
    r4->ptr = r5->data;
    r4->b = r5->b;
}

void func_02020d98(void *param)
{
    FrameLocals locals;

    func_0201cf90(param, locals.buffer, 0, 0x37, 0x39, (unsigned int) data_021c21cc);
    func_0201cf90(param, locals.buffer, 1, 0x3a, 0x3c, (unsigned int) data_021c21e4);

    locals.pair[0] = 2;
    locals.pair[1] = locals.pair[0] - 1;

    func_0201cec8(param, locals.buffer);
    func_0202da74(param, data_020d9280);
    func_02068388(*(int *) ((char *) param + 0x40), 1);
}
