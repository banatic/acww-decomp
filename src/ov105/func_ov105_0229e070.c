/* func_ov105_0229e070 @ 0x0229e070, 0x30 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *ptr);
extern void func_ov002_02208098(void *obj, unsigned char byte);
extern void func_ov105_0229d17c(void *obj);

struct UnkStruct_0229e070 {
    char pad_00[0x2bd];
    unsigned char unk_2BD;
    char pad_2BE[0x24a4 - 0x2be];
    char unk_24A4;
};

void func_ov105_0229e070(struct UnkStruct_0229e070 *obj)
{
    if (func_0208e484(&obj->unk_24A4)) {
        func_ov002_02208098(obj, obj->unk_2BD);
    }
    func_ov105_0229d17c(obj);
}
