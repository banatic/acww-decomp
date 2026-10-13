/* func_020b4ad4 @ 0x020b4ad4, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9484(void *obj);
extern char data_020e3e68;
extern char data_020e5230;

typedef struct UnkStruct_020b4ad4 {
    void *unk_00;
    unsigned char pad_04[0x20];
    unsigned int unk_24;
    unsigned int unk_28;
    unsigned int unk_2C;
} UnkStruct_020b4ad4;

UnkStruct_020b4ad4 *func_020b4ad4(UnkStruct_020b4ad4 *obj)
{
    func_020a9484(obj);
    obj->unk_00 = (void *) &data_020e3e68;
    obj->unk_00 = (void *) &data_020e5230;
    obj->unk_24 = 0;
    obj->unk_28 = 0;
    obj->unk_2C = 0;
    return obj;
}
