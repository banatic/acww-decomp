/* func_0201a19c @ 0x0201a19c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201a2e8(void *obj, unsigned int value);
extern void func_0201a1d4(void *obj, unsigned int value, int flag);
extern unsigned int data_020c8170[];

typedef struct {
    unsigned char pad_00[0x78];
    unsigned int unk_78;
    unsigned int unk_7C;
} UnkStruct_0201a19c;

void func_0201a19c(UnkStruct_0201a19c *obj, int index)
{
    if (index < 0 || index >= 2) {
        return;
    }
    if (func_0201a2e8(obj, obj->unk_78) == 0) {
        obj->unk_7C = obj->unk_78;
    }
    func_0201a1d4(obj, data_020c8170[index], 0);
}
