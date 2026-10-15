/* func_0203f130 @ 0x0203f130, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02003564(void *);
extern int data_020dab34;

typedef struct {
    void *unk_00;
    unsigned char pad_04[0xD0];
    int unk_D4;
    int unk_D8;
    int unk_DC;
} UnkStruct_0203f130;

UnkStruct_0203f130 *func_0203f130(UnkStruct_0203f130 *obj)
{
    func_02003564(obj);
    obj->unk_00 = &data_020dab34;
    obj->unk_D4 = 0;
    obj->unk_D8 = 0;
    obj->unk_DC = 0;
    return obj;
}
