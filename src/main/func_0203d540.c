/* func_0203d540 @ 0x0203d540, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a81b8(void *obj);
extern char data_020da97c;

typedef struct {
    void *vtable;
    char pad_04[0x1c];
    unsigned int unk_20;
    unsigned int unk_24;
    unsigned int unk_28;
    unsigned int unk_2C;
} UnkStruct_0203d540;

UnkStruct_0203d540 *func_0203d540(UnkStruct_0203d540 *obj)
{
    func_020a81b8(obj);
    obj->vtable = &data_020da97c;
    obj->unk_20 = 0;
    obj->unk_24 = 0;
    obj->unk_28 = 0;
    obj->unk_2C = 0;
    return obj;
}
