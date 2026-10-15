/* func_02010ff4 @ 0x02010ff4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02010ff4 {
    char pad_00[0x60];
    int unk_60;
};

extern void func_02003300(struct UnkStruct_02010ff4 *p, int flag);
extern int func_020310c8(int arg);

int func_02010ff4(struct UnkStruct_02010ff4 *s)
{
    int result;

    func_02003300(s, 0);
    result = func_020310c8(0);
    s->unk_60 = result;
    return result;
}
