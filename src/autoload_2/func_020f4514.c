/* func_020f4514 @ 0x020f4514, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213efb4;
extern void NNS_SndHeapLoadState(int a, int b);

struct Object {
    void *vt;
};

struct State {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
};

extern struct State data_021fd1bc;

void *func_020f4514(void *obj)
{
    struct Object *self = (struct Object *) obj;
    int arg;

    self->vt = (void *) &data_0213efb4;
    arg = data_021fd1bc.unk_28;
    data_021fd1bc.unk_2C = 0;
    NNS_SndHeapLoadState(arg, 0);
    return self;
}
