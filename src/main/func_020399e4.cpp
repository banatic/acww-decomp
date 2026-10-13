/* func_020399e4 @ 0x020399e4, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020399e4 {
    char pad_00[0x10];
    int unk_10;
    char pad1[0x18];
    int unk_2C;
    char pad2[8];
    unsigned char unk_38;
    unsigned char unk_39;
    char pad_3A[0x16];
    int unk_50;
    unsigned char unk_54;
    unsigned char unk_55;
    char pad_56[2];
    int unk_58;
};

extern "C" {
extern void *func_020a9034(int, int, int);
extern void func_02051694(UnkStruct_020399e4 *);
extern int data_021c8c9c;
}

struct UnkStruct_020399e4_2 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int v3();
};

struct UnkStruct_020399e4_3 {
    char pad_00[0xc];
    volatile int unk_0C;
    char pad1[0x78];
    UnkStruct_020399e4_2 sub88;
    char pad2[0x10];
    UnkStruct_020399e4 *unk_9C;
};

extern "C" void func_020399e4(UnkStruct_020399e4_3 *obj)
{
    UnkStruct_020399e4 *q;

    if (obj->unk_0C == 0) {
        return;
    }
    if (obj->unk_9C != 0) {
        return;
    }
    obj->unk_9C = (UnkStruct_020399e4 *) func_020a9034(obj->unk_0C * 8 + 0x1c0, 8, 2);
    if (obj->unk_9C == 0) {
        return;
    }
    obj->unk_9C->unk_2C = 4;
    q = obj->unk_9C;
    q->unk_10 = obj->sub88.v3();
    if (data_021c8c9c == 0) {
        obj->unk_9C->unk_50 = 3;
    } else {
        obj->unk_9C->unk_50 = 2;
    }
    obj->unk_9C->unk_58 = 1;
    obj->unk_9C->unk_55 = 1;
    obj->unk_9C->unk_39 = 0xe;
    obj->unk_9C->unk_38 = 0xd;
    func_02051694(obj->unk_9C);
}
