/* func_02027dcc @ 0x02027dcc, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Pair {
    int a;
    int b;
};
struct UnkStruct_02027dcc {
    char pad_00[0x830];
    int unk_830;
};
struct UnkStruct_02027dcc_2 {
    char pad_00[0x100];
    struct UnkStruct_02027dcc *sub;
    char pad_104[0x5c];
    void *unk_160;
};

extern int func_0202d9c4(void *);
extern int func_0209bc40(int);
extern int func_0209bb70(int);
extern void func_02015330(void *, int, int, int, int);
extern void func_0202dbf0(void *, struct Pair);
extern int func_0208150c(int);
extern int func_0209b4cc(void *, int);
extern void func_0207bae8(int, int, int, int);
extern void func_0209b56c(void *);
extern struct Pair data_020d8e00;

extern unsigned char data_021e5a2c[];

void func_02027dcc(struct UnkStruct_02027dcc_2 *self)
{
    int arg5;
    if (func_0209bc40(func_0202d9c4(self)) == 19) {
        arg5 = 0;
        func_02015330(self, func_0209bb70(func_0202d9c4(self)), 0, 5, arg5);
        func_0202dbf0(self, data_020d8e00);
    }
    {
        int r4 = func_0208150c(self->sub->unk_830);
        int r2 = func_0209b4cc(self->unk_160, 1);
        func_0207bae8((unsigned int) data_021e5a2c, r4, r2, ~19);
        func_0209b56c(self->unk_160);
    }
}
