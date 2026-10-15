/* func_02069d24 @ 0x02069d24, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_0206781c(void *);
extern "C" void func_0206bb9c(void *object, int code, const void *message);
extern "C" void func_020a9334(void *, int);
extern "C" void func_020a7994(void *, int);
extern "C" char data_020df14c;

class MyVirt {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
    virtual int f3();
};

typedef struct UnkStruct_02069d24 {
    char pad_00[0x24];
    void *base;
} UnkStruct_02069d24;

extern "C" void func_02069d24(UnkStruct_02069d24 *obj)
{
    int res1, res2;

    if (func_0206781c(obj->base) == 0) {
        func_0206bb9c(obj, 0xde6, &data_020df14c);
    }

    res1 = ((MyVirt *) ((char *) obj->base + 0x1d4c))->f3();
    func_020a9334(obj, res1);

    res2 = ((MyVirt *) ((char *) obj->base + 0x1d4c))->f3();
    func_020a7994((char *) obj->base + 0x1a58, res2);

    *(int *) ((char *) obj->base + 0x1a60) = 1;
}
