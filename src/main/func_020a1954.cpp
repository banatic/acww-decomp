/* func_020a1954 @ 0x020a1954, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class Member {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
};

struct UnkStruct_020a1954 {
    int pad_00;
    int pad_04;
    int unk_08;
};

struct Owner {
    char pad_00[0x54];
    Member m;
    char pad1[0x72 - 0x54 - sizeof(Member)];
    char c;
};

extern "C" UnkStruct_020a1954 *func_020682e0(int);
extern "C" void func_02068440(UnkStruct_020a1954 *);
extern "C" void func_02068340(UnkStruct_020a1954 *, Member *);
extern "C" void func_020a8164(Member *, int);

extern "C" int func_020a1954(Owner *owner, int arg1, char arg2)
{
    UnkStruct_020a1954 *ptr = func_020682e0(0);
    owner->m.vf2();
    func_020a8164(&owner->m, arg1);
    owner->c = arg2;
    func_02068440(ptr);
    func_02068340(ptr, &owner->m);
    ptr->unk_08 = 1;
    return 1;
}
