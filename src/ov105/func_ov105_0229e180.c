/* func_ov105_0229e180 @ 0x0229e180, 0x4c bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229e180 {
    char pad_to_2ba[0x2ba];
    unsigned char unk_2BA;
    char pad_between[2];
    unsigned char unk_2BD;
    char pad_to_24a4[0x24a4 - 0x2be];
    char unk_24A4;
};

extern int func_ov002_02209f64(void *p);
extern void func_ov002_02208098(struct UnkStruct_0229e180 *obj, unsigned char b);
extern void func_ov105_0229d3b4(struct UnkStruct_0229e180 *obj, unsigned char b);
extern void func_ov105_0229f25c(struct UnkStruct_0229e180 *obj);
extern void func_ov105_0229d17c(struct UnkStruct_0229e180 *obj);

void func_ov105_0229e180(struct UnkStruct_0229e180 *obj)
{
    if (func_ov002_02209f64(&obj->unk_24A4) == 0) {
        func_ov002_02208098(obj, obj->unk_2BD);
        if (obj->unk_2BD == 7) {
            func_ov105_0229d3b4(obj, obj->unk_2BA);
        }
        func_ov105_0229f25c(obj);
    }
    func_ov105_0229d17c(obj);
}
