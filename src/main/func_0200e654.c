/* func_0200e654 @ 0x0200e654, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020961d0(int);
extern void func_0205df14(char *ptr, unsigned char val);
extern void func_02011138(void *dst, void *src);
extern void func_020103c0(void *a, void *b);
extern void func_02010424(void *a);
extern unsigned char data_020c75c8[];

struct UnkStruct_0200e654 {
    char pad_00[0x59c];
    char unk_59C;
    char pad_59D[0x800 - 0x59c - 1];
    int unk_800;
};

void func_0200e654(struct UnkStruct_0200e654 *s)
{
    unsigned short local[4];
    int idx;
    idx = func_020961d0(s->unk_800);
    func_0205df14(&s->unk_59C, data_020c75c8[idx]);
    func_02011138(local, s);
    local[1] = local[0];
    func_020103c0(s, &local[1]);
    func_02010424(s);
}
