/* func_ov051_02260f04 @ 0x02260f04, 0x28 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov051_022615c0;
extern unsigned char func_ov051_022605e8(void *, int);
extern void func_0206844c(unsigned int, unsigned char *, unsigned int);

struct UnkStruct_02260f04 {
    char pad_00[0x40];
    unsigned int unk_40;
};

void func_ov051_02260f04(struct UnkStruct_02260f04 *obj)
{
    unsigned char local;
    local = func_ov051_022605e8(obj, 0x11);
    func_0206844c(obj->unk_40, &local, data_ov051_022615c0);
}
