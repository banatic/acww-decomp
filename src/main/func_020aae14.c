/* func_020aae14 @ 0x020aae14, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020aac1c(void *obj);
extern void func_020ab558(void *ptr);

struct UnkStruct_020aae14 {
    unsigned char pad_00[0x28];
    unsigned int unk_28;
    unsigned char pad_2C[0x34 - 0x2C];
    void *unk_34;
};

void func_020aae14(struct UnkStruct_020aae14 *obj)
{
    func_020aac1c(obj);
    func_020ab558(obj->unk_34);
    obj->unk_28 = 0;
    obj->unk_34 = 0;
}
