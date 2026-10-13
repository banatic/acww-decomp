/* func_0201c828 @ 0x0201c828, 0xd4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0201c828 {
  public:
    unsigned char pad_00[0x44];
    int state;
    int unk_48;
    void (UnkStruct_0201c828::*pmf)(int);
};

extern void (UnkStruct_0201c828::*data_0213dd98)(int);
extern "C" int func_020164a0(int, int);
extern "C" int func_0201c8fc(UnkStruct_0201c828 *, int, int);

extern "C" void func_0201c828(UnkStruct_0201c828 *self, int arg, int arg2)
{
    if (arg2 != self->state && self->state != 5) {
        self->pmf = data_0213dd98;
        self->state = 5;
    } else if (self->pmf == 0) {
        switch (func_020164a0(arg + 0x334, 0) - 0xe5) {
            case 0:
            case 1:
                if (arg2 == 1 && func_0201c8fc(self, arg, 1)) {
                    self->state = arg2;
                }
                break;
            case 2:
            case 3:
                if ((arg2 == 2 || arg2 == 4) && func_0201c8fc(self, arg, 2)) {
                    self->state = arg2;
                }
                break;
            case 4:
            case 5:
                if ((unsigned char) (arg2 + 0xfd) <= 1 && func_0201c8fc(self, arg, 3)) {
                    self->state = arg2;
                }
                break;
        }
    }
    if (self->pmf) {
        (self->*self->pmf)(arg);
    }
}
