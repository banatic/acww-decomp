/* func_ov110_0229e60c @ 0x0229e60c, 0x7e bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void *func_ov002_02207f60(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_ov002_02207e90(void *, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov110_0229e1dc(void *);
extern void func_ov110_0229c2b8(void *, int);
extern void func_02002708(int);

struct UnkStruct_0229e60c {
    char pad_00[0x98];
    void *unk_98;
    void *unk_9C;
};

void func_ov110_0229e60c(void *p)
{
    struct UnkStruct_0229e60c *s = (struct UnkStruct_0229e60c *) p;
    int cond;
    int zero = 0;

    cond = func_ov002_02207f48(s, 0);
    func_ov002_02207e80(s, 6, zero, zero);
    s->unk_98 = func_ov002_02207f60(s);
    if (cond != 0) {
        func_ov110_0229e1dc(s);
        func_ov002_02207f20(s, 2, zero, 1, 0x30);
        func_ov002_02207e90(s, 0x80);
        func_ov110_0229c2b8(s, 0x80);
        func_02002708(4);
        func_ov002_02207e80(s, 4, zero, zero);
        s->unk_9C = func_ov002_02207f60(s);
        func_ov002_02208090(s, 3);
    }
}
