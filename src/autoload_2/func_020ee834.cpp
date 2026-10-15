/* func_020ee834 @ 0x020ee834, 0x74 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

class UnkStruct_020ee834 {
  public:
    virtual void vfunc_00();
    virtual void vfunc_04();
    virtual void vfunc_08();
};

struct Node {
    int unk_00;
    Node *next;
    UnkStruct_020ee834 *obj;
};

typedef void (UnkStruct_020ee834::*PMF)();

struct UnkStruct_020ee834_2 {
    Node *head;
    int pad_04;
    PMF pmf;
};

extern Node *data_021fcff4;

extern "C" int func_020ee834(UnkStruct_020ee834_2 *self)
{
    if (self->pmf == 0) {
        return 1;
    }
    Node *cur = self->head;
    data_021fcff4 = cur;
    if (cur != 0) {
        do {
            UnkStruct_020ee834 *obj = cur->obj;
            Node *next = cur->next;
            (obj->*self->pmf)();
            cur = next;
            data_021fcff4 = cur;
        } while (cur != 0);
    }
    return 1;
}
