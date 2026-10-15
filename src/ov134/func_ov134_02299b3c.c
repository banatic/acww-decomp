/* func_ov134_02299b3c @ 0x02299b3c, 0x32 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_02299a14(void *obj);
extern void func_ov134_02299a00(void *obj);
extern void func_ov002_0220a4c8(void);

struct UnkStruct_02299b3c {
    char data[0x4c];
};
struct UnkStruct_02299b3c_2 {
    char pad_00[0x18];
    struct UnkStruct_02299b3c sub;
    int unk_64;
    int unk_68;
    int unk_6C;
};

void func_ov134_02299b3c(struct UnkStruct_02299b3c_2 *obj)
{
    int diff;
    func_ov134_02299a14(obj);
    func_ov134_02299a00(obj);
    diff = obj->unk_6C - obj->unk_64;
    if (diff >= 4 || diff <= -4) {
        // clang-format off
        asm {
            mov r0, obj
            add r0, #0x18
        }
        // clang-format on
        func_ov002_0220a4c8();
        obj->unk_6C = obj->unk_64;
    }
}
