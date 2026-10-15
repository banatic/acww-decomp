/* func_ov121_0229a53c @ 0x0229a53c, 0x2c bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov121_0229a1b0(void *obj);
extern void func_ov002_022096d8(void *ptr, int value);
extern unsigned char *func_ov002_02208098(void *obj, unsigned char value);

typedef struct {
    char pad_00[0xB2];
    char unk_B2;
} UnkStruct_0229a53c;

void func_ov121_0229a53c(UnkStruct_0229a53c *obj)
{
    obj->unk_B2 = 8;
    func_ov121_0229a1b0(obj);
    func_ov002_022096d8((char *) obj + 0x528, 0);
    func_ov002_02208098(obj, 16);
}
