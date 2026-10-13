/* func_020eea4c @ 0x020eea4c, 0x80 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

class UnkStruct_020eea4c {
  public:
    virtual void m0();
};

struct Node {
    char pad_00[0x10];
    UnkStruct_020eea4c *obj;
};

typedef void (UnkStruct_020eea4c::*PMF)();

struct UnkStruct_020eea4c_2 {
    Node *head;
    PMF pmf;
};

extern "C" Node *func_01ffcffc(Node *p);

extern "C" int func_020eea4c(UnkStruct_020eea4c_2 *self)
{
    if (self->pmf == 0) {
        return 1;
    }
    Node *p = self->head;
    if (p != 0) {
        PMF *pmf = &self->pmf;
        if (p != 0) {
            do {
                Node *next = func_01ffcffc(p);
                (p->obj->**pmf)();
                p = next;
            } while (p != 0);
        }
    }
    return 1;
}
