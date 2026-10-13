/* func_ov099_0229c9d0 @ 0x0229c9d0, 0x64 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229c9d0 {
    char pad_00[0x218c];
    char sub[0x0779];
    unsigned char unk_2905;
    char pad_2906[1];
    unsigned char unk_2907;
} UnkStruct_0229c9d0;

extern int func_ov099_0229cf30(UnkStruct_0229c9d0 *obj, unsigned char byte);
extern int func_ov099_0229cf20(UnkStruct_0229c9d0 *obj, unsigned char byte);
extern int func_ov099_0229cc74(UnkStruct_0229c9d0 *obj, unsigned char byte);
extern void func_ov002_02207cf0(char *sub);
extern void func_ov002_02207cf8(char *sub);

void func_ov099_0229c9d0(UnkStruct_0229c9d0 *obj)
{
    if (func_ov099_0229cf30(obj, obj->unk_2907) != 0 || func_ov099_0229cf20(obj, obj->unk_2907) != 0) {
        if (func_ov099_0229cc74(obj, obj->unk_2907) != 0) {
            func_ov002_02207cf0(obj->sub);
        } else {
            obj->unk_2905 = obj->unk_2907;
            func_ov002_02207cf8(obj->sub);
        }
    } else {
        func_ov002_02207cf0(obj->sub);
    }
}
