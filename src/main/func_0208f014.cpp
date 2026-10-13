/* func_0208f014 @ 0x0208f014, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208f014_2 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
};

struct UnkStruct_0208f014_3 {
    char pad_00[0x10];
    int unk_10;
    char pad1[0x18];
    int unk_2C;
    char pad2[8];
    unsigned char unk_38;
    unsigned char unk_39;
    char pad3[0x16];
    int unk_50;
    char pad_54[1];
    unsigned char unk_55;
};

struct UnkStruct_0208f014 {
    char pad_00[0x18];
    int unk_18;
    char pad1[0x2c];
    UnkStruct_0208f014_3 *unk_48;
    UnkStruct_0208f014_2 sub;
    char pad2[0x22];
    unsigned char unk_72;
    char pad3[2];
    unsigned char unk_75;
};

extern "C" {
extern void *data_020d0b7c[];
extern unsigned char data_020d0b78[];
extern UnkStruct_0208f014_3 *func_020a9034(void *a, int b, int c);
extern void func_02051648(UnkStruct_0208f014_3 *obj);
extern void func_02051694(UnkStruct_0208f014_3 *obj);

void func_0208f014(UnkStruct_0208f014 *s)
{
    UnkStruct_0208f014_3 *obj;
    if (s->unk_48 != 0) {
        return;
    }
    s->unk_48 = func_020a9034(data_020d0b7c[s->unk_18], 6, 2);
    if (s->unk_48 == 0) {
        return;
    }
    s->unk_48->unk_2C = 4;
    obj = s->unk_48;
    obj->unk_10 = s->sub.v3();
    if (s->unk_72 != 0) {
        s->unk_48->unk_50 = 2;
    }
    s->unk_48->unk_55 = 1;
    func_02051648(s->unk_48);
    s->unk_48->unk_39 = 0;
    s->unk_48->unk_38 = data_020d0b78[s->unk_18];
    func_02051694(s->unk_48);
    s->unk_75 = 1;
}
}
