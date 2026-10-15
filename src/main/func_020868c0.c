/* func_020868c0 @ 0x020868c0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0209529c(void *obj);
extern int func_02003780(void *ptr);

struct UnkStruct_020868c0 {
    char pad_00[0x1e];
    char unk_1E[0x10];
    char unk_2E[0x10];
    unsigned short unk_3E;
};

struct UnkStruct_020868c0 *func_020868c0(struct UnkStruct_020868c0 *obj)
{
    func_0209529c(obj);
    func_02003780(obj->unk_1E);
    func_02003780(obj->unk_2E);
    obj->unk_3E = 0xFFF1;
    return obj;
}
