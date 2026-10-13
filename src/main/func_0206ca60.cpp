/* func_0206ca60 @ 0x0206ca60, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206ca60 {
    char pad_00[0x1a58];
    void *data;
    char pad_1A5C[4];
    unsigned int flag;
};

struct UnkStruct_0206ca60_2 {
    char pad_00[0x2c];
    struct UnkStruct_0206ca60 *unk_2C;
};

class UnkStruct_0206ca60_3 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual int vf3();
};

extern "C" {
UnkStruct_0206ca60_3 *func_02068034(struct UnkStruct_0206ca60 *);
void func_020a9334(struct UnkStruct_0206ca60_2 *, int);
void func_020a7994(void *, int);
void func_0206ca60(struct UnkStruct_0206ca60_2 *);
}

void func_0206ca60(struct UnkStruct_0206ca60_2 *obj)
{
    UnkStruct_0206ca60_3 *sc;
    int val;

    sc = func_02068034(obj->unk_2C);
    val = sc->vf3();
    func_020a9334(obj, val);

    sc = func_02068034(obj->unk_2C);
    val = sc->vf3();
    func_020a7994((void *) &obj->unk_2C->data, val);

    obj->unk_2C->flag = 1;
}
