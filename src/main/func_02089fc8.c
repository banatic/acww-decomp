/* func_02089fc8 @ 0x02089fc8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02089fc8 UnkStruct_02089fc8;
struct UnkStruct_02089fc8 {
    unsigned char pad_00[0x38];
    UnkStruct_02089fc8 *unk_38;
};
extern UnkStruct_02089fc8 *data_021d3120;
extern void func_02089fe4(UnkStruct_02089fc8 *obj);

void func_02089fc8(UnkStruct_02089fc8 *obj)
{
    func_02089fe4(obj);
    obj->unk_38 = data_021d3120;
    data_021d3120 = obj;
}
