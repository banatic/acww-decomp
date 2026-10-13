/* func_02067218 @ 0x02067218, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02067218_2 {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
};

struct UnkStruct_02067218 {
    unsigned char pad_00[0x14a8];
    struct UnkStruct_02067218_2 *ptr;
    unsigned char pad_14AC[0x9cb];
    unsigned char unk_1E77;
    signed char unk_1E78;
};

extern char data_021f43f8;

extern void func_020a8164(void *p, signed char *q, signed char c);
extern void func_0206844c(void *s, void *g, int i);
extern void func_0206726c(void *s);
extern void func_0206741c(void *s);
extern void func_02067c20(void *s);

void func_02067218(struct UnkStruct_02067218 *s)
{
    signed char v;
    s->ptr->unk_1E = s->unk_1E77;
    v = s->unk_1E78;
    if (v != 0) {
        func_020a8164(s->ptr, &s->unk_1E78, v);
    }
    func_0206844c(s, &data_021f43f8, 0);
    func_0206726c(s);
    func_0206741c(s);
    func_02067c20(s);
}
