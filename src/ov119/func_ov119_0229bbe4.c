/* func_ov119_0229bbe4 @ 0x0229bbe4, 0x30 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229bbe4 {
    char pad_00[0x9a];
    short unk_9A;
};

extern void func_ov119_0229a410(struct UnkStruct_0229bbe4 *, int);
extern int func_0206fe60(void);
extern void func_ov119_0229bc30(struct UnkStruct_0229bbe4 *);
extern void func_ov119_0229bc14(struct UnkStruct_0229bbe4 *);

void func_ov119_0229bbe4(struct UnkStruct_0229bbe4 *obj)
{
    obj->unk_9A = -1;
    func_ov119_0229a410(obj, 4);
    if (func_0206fe60() != 0) {
        func_ov119_0229bc30(obj);
    } else {
        func_ov119_0229bc14(obj);
    }
}
