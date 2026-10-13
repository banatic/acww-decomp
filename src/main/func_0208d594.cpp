/* func_0208d594 @ 0x0208d594, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_020b45d0(void *, unsigned char, int, int, int, int);
extern "C" void func_02051648(void *);
extern "C" void func_02051694(void *);

typedef struct UnkStruct_0208d594_2 {
    char pad_00[0x10];
    int unk_10;
} UnkStruct_0208d594_2;

class FieldBC {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int method();
};

typedef struct UnkStruct_0208d594 {
    char pad_00[0x3C];
    UnkStruct_0208d594_2 *unk_3C;
    char pad_40[0x4D - 0x40];
    unsigned char unk_4D;
    char pad_4E[0x62 - 0x4E];
    unsigned char unk_62;
    char pad_63[0xBC - 0x63];
    FieldBC unk_BC;
} UnkStruct_0208d594;

extern "C" void func_0208d594(UnkStruct_0208d594 *p)
{
    if (p->unk_3C && p->unk_4D) {
        p->unk_4D = 0;
        func_020b45d0(&p->unk_BC, p->unk_62, 2, 6, 0, 1);
        UnkStruct_0208d594_2 *inner = p->unk_3C;
        inner->unk_10 = p->unk_BC.method();
        func_02051648(p->unk_3C);
        func_02051694(p->unk_3C);
    }
}
