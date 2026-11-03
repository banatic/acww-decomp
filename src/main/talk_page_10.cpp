/* talk_page_10: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206ca60 @ 0x0206ca60, 0x48 bytes, Thumb
 * func_0206ca18 @ 0x0206ca18, 0x48 bytes, Thumb
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
}

typedef struct UnkStruct_0206ca18 {
    char pad_00[0x2c];
    char *unk_2C;
} UnkStruct_0206ca18;

class VirtualObj {
  public:
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual void vfunc_08();
    virtual int getValue();
};

extern "C" VirtualObj *func_02068010(char *p);

extern "C" {
void func_0206ca60(struct UnkStruct_0206ca60_2 *obj);
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

extern "C" void func_0206ca18(UnkStruct_0206ca18 *self)
{
    VirtualObj *q;
    int v;

    q = func_02068010(self->unk_2C);
    v = q->getValue();
    func_020a9334((struct UnkStruct_0206ca60_2 *) self, v);

    q = func_02068010(self->unk_2C);
    v = q->getValue();
    func_020a7994((void *) (self->unk_2C + 0x1a58), v);

    *(int *) (self->unk_2C + 0x1a60) = 1;
}
