/* func_0208a9e4 @ 0x0208a9e4, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Node {
    char pad_00[0x10];
    int unk_10;
};

struct UnkStruct_0208a9e4 {
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

struct UnkStruct_0208a9e4_2 {
    char pad_00[0x60];
    UnkStruct_0208a9e4 unk_60;
    char pad_64[0x2c];
    UnkStruct_0208a9e4 unk_90;
    char pad_94[0x2c];
    Node *c0;
    Node *c4;
};

extern "C" void func_02051694(Node *);
extern "C" void func_0208a664(UnkStruct_0208a9e4_2 *);

extern "C" void func_0208a9e4(UnkStruct_0208a9e4_2 *self, int flag)
{
    Node *n;

    n = self->c0;
    if (n != 0) {
        n->unk_10 = self->unk_60.m3();
        func_02051694(self->c0);
    }
    n = self->c4;
    if (n != 0) {
        n->unk_10 = self->unk_90.m3();
        func_02051694(self->c4);
    }
    if (flag != 0) {
        func_0208a664(self);
    }
}
