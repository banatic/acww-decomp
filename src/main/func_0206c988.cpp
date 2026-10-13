/* func_0206c988 @ 0x0206c988, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0206c988 {
  public:
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

typedef struct {
    char pad_00[0x2c];
    void *unk_2C;
} UnkStruct_0206c988_2;

typedef struct {
    char pad_00[0x1a58];
    int unk_1A58;
    char pad_1A5C[4];
    int unk_1A60;
} BigStruct;

extern "C" UnkStruct_0206c988 *func_02067fa4(void *obj);
extern "C" int func_020a9334(void *a, int b);
extern "C" int func_020a7994(void *a, int b);

extern "C" void func_0206c988(UnkStruct_0206c988_2 *param)
{
    UnkStruct_0206c988 *obj = func_02067fa4(param->unk_2C);
    int ret = obj->m3();
    func_020a9334(param, ret);

    obj = func_02067fa4(param->unk_2C);
    ret = obj->m3();
    func_020a7994(&((BigStruct *) param->unk_2C)->unk_1A58, ret);
    ((BigStruct *) param->unk_2C)->unk_1A60 = 1;
}
