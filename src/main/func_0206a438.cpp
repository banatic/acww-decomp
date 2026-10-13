/* func_0206a438 @ 0x0206a438, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    char *unk_24;
} UnkStruct_0206a438;

extern "C" int func_02067a74(void *);
extern "C" void func_0206bb9c(UnkStruct_0206a438 *, int, void *);
extern "C" void func_020a9334(UnkStruct_0206a438 *, int);
extern "C" void func_020a7994(void *, int);

class UnkStruct_0206a438_2 {
  public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual int f3(); // offset 0xc
};

extern unsigned char data_020df1b8[];

extern "C" void func_0206a438(UnkStruct_0206a438 *obj)
{
    if (func_02067a74(obj->unk_24) == 0) {
        func_0206bb9c(obj, 0xc39, (void *) data_020df1b8);
    }

    int result1 = ((UnkStruct_0206a438_2 *) (obj->unk_24 + 0x1c70))->f3();
    func_020a9334(obj, result1);

    int result2 = ((UnkStruct_0206a438_2 *) (obj->unk_24 + 0x1c70))->f3();
    func_020a7994(obj->unk_24 + 0x1a58, result2);

    *(int *) (obj->unk_24 + 0x1a60) = 0;
}
