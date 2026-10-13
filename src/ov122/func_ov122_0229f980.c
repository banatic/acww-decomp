/* func_ov122_0229f980 @ 0x0229f980, 0x26 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229f980;

extern unsigned short *func_ov122_0229f634(struct UnkStruct_0229f980 *obj, unsigned char field);

struct UnkStruct_0229f980 {
    char pad_00[0xac];
    unsigned char unk_AC;
};

unsigned short func_ov122_0229f980(struct UnkStruct_0229f980 *obj)
{
    if (obj->unk_AC == 0) {
        return 0;
    }
    return func_ov122_0229f634(obj, obj->unk_AC)[obj->unk_AC - 1];
}
