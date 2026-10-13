/* func_ov003_02218bf0 @ 0x02218bf0, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern int func_02073908(unsigned int, unsigned int);
extern int func_0200f290(void *, int);
extern void func_ov003_022189d8(void *);

struct UnkStruct_02218bf0 {
    char pad_00[0x800];
    unsigned int unk_800;
};

void func_ov003_02218bf0(void *param)
{
    if (func_02073908(data_020ccf94, ((struct UnkStruct_02218bf0 *) param)->unk_800) != 0) {
        return;
    }
    if (func_0200f290(param, 0x1c) == 0) {
        return;
    }
    func_ov003_022189d8(param);
}
