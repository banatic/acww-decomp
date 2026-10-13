/* func_ov122_0229effc @ 0x0229effc, 0x36 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov122_0229f034(void *, const void *, int);

typedef struct {
    char pad_00[0xbc];
    unsigned char *data;
} UnkStruct_0229effc;

void func_ov122_0229effc(UnkStruct_0229effc *obj)
{
    func_ov122_0229f034(obj, obj->data + 0x44, 0xa);
    func_ov122_0229f034(obj, obj->data + 0xd8, 0x10);
    func_ov122_0229f034(obj, obj->data + 0x58, 0x40);
}
