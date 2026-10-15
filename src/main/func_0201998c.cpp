/* func_0201998c @ 0x0201998c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0201998c;
typedef void (UnkStruct_0201998c::*Pmf)(void *);
class Node {
  public:
    char pad_00[8];
    Pmf pmf;
};
class UnkStruct_0201998c {
  public:
    char pad_00[0x14];
    int unk_14;
    char pad_18[8];
    Node *unk_20;
};
extern "C" int func_02019de8(UnkStruct_0201998c *);

extern "C" void func_02019af8(UnkStruct_0201998c *, int);
extern "C" void func_0201998c(UnkStruct_0201998c *self, void *arg)
{
    func_02019af8(self, (int) arg);
    Node *n = self->unk_20;
    if (n && n->pmf) {
        (self->*(n->pmf))(arg);
    }
    if (func_02019de8(self)) {
        self->unk_14 = 0;
    }
}
