/* func_0206d9c0 @ 0x0206d9c0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020df1d0;
extern void func_020a8c38(void *);

struct UnkStruct_0206d9c0 {
    unsigned char *unk_00;
};

struct UnkStruct_0206d9c0 *func_0206d9c0(struct UnkStruct_0206d9c0 *obj)
{
    obj->unk_00 = &data_020df1d0;
    func_020a8c38(obj);
    return obj;
}
