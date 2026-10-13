/* func_ov105_0229c6a0 @ 0x0229c6a0, 0x70 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xac];
    int unk_AC;
    int unk_B0;
    char pad_B4[0x2bb - 0xb4];
    unsigned char unk_2BB;
} UnkStruct_0229c6a0;

extern void func_ov105_0229d0f8(void *obj, unsigned char b);
extern int func_ov105_0229d530(void *obj, unsigned char b);
extern int func_ov105_0229d4c4(void *obj, unsigned char b);
extern int func_0206fe54(void);
extern void func_ov002_02208098(void *obj, int param);
extern void func_ov094_0229b1d8(void *ptr);

void func_ov105_0229c6a0(UnkStruct_0229c6a0 *obj)
{
    unsigned char b = obj->unk_2BB;
    func_ov105_0229d0f8(obj, b);
    obj->unk_AC = func_ov105_0229d530(obj, b);
    obj->unk_B0 = func_ov105_0229d4c4(obj, b);
    if (func_0206fe54() != 0) {
        obj->unk_AC -= 2;
        obj->unk_B0 -= 2;
    }
    func_ov002_02208098(obj, 0x1c);
    func_ov094_0229b1d8((char *) obj + 0x0d5c);
}
