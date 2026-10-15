/* func_020a91f0 @ 0x020a91f0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a92b0(void *obj, int arg);
extern char data_020e3dc4;

struct UnkStruct_020a91f0 {
    void *unk_00;
    char pad_04[0x28];
    int unk_2C;
};

struct UnkStruct_020a91f0 *func_020a91f0(struct UnkStruct_020a91f0 *obj)
{
    func_020a92b0(obj, 1);
    obj->unk_00 = &data_020e3dc4;
    obj->unk_2C = 0;
    return obj;
}
