/* func_ov003_02215dfc @ 0x02215dfc, 0x10 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200fb34(void *obj, int val);

struct UnkStruct_02215dfc {
    unsigned char pad_00[0x7d4];
    signed short unk_7D4;
};

void func_ov003_02215dfc(struct UnkStruct_02215dfc *obj)
{
    func_0200fb34(obj, obj->unk_7D4);
}
