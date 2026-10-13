/* func_0201d71c @ 0x0201d71c, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0201d71c {
    unsigned char pad_00[0x124];
    unsigned short unk_124;
    unsigned char pad_126[0x19c - 0x124 - 2];
    unsigned short unk_19C;
    unsigned char pad_19E[0x1a0 - 0x19c - 2];
    int unk_1A0;
} UnkStruct_0201d71c;

typedef struct Pair {
    int a;
    int b;
} Pair;

extern void func_020984e8(void);
extern int func_02099734(void);
extern int func_02099e9c(unsigned short *p);
extern void func_02098f0c(int a, unsigned short *b, int c, int d);
extern void func_02098a24(int a, int b, int c);
extern void func_02027170(unsigned short *p, int v);
extern void func_020154b4(UnkStruct_0201d71c *s, unsigned short *p, int a, int b, int c);
extern void func_0202dbf0(UnkStruct_0201d71c *s, Pair p);
extern Pair data_020d9060;

int func_0201d71c(UnkStruct_0201d71c *s)
{
    int ret;
    int status;
    unsigned short tmp[2];

    if (s->unk_1A0 <= 0) {
        goto fail;
    }
    if (s->unk_124 == 0xfff1) {
        goto fail;
    }

    func_020984e8();
    ret = func_02099734();
    status = func_02099e9c(&s->unk_124);
    if (status < 0) {
        goto fail;
    }

    tmp[0] = 0xfff1;
    func_02098f0c(ret, tmp, status, 0);
    func_02098a24(ret, s->unk_1A0, 1);
    func_02027170(&tmp[1], s->unk_1A0);
    s->unk_19C = tmp[1];

    func_020154b4(s, &s->unk_19C, 0, 5, 0);
    func_0202dbf0(s, data_020d9060);

    return 1;
fail:
    return 0;
}
