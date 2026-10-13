/* func_02065ed0 @ 0x02065ed0, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02065ed0 {
    unsigned char pad_00[0xFC];
    unsigned short unk_FC;
};

extern void func_02065ef4(struct UnkStruct_02065ed0 *obj, int param);

unsigned short func_02065ed0(struct UnkStruct_02065ed0 *obj, unsigned short value, int param)
{
    unsigned short old = obj->unk_FC;
    if (param == 0xFF) {
        param = 0;
    }
    obj->unk_FC = value;
    func_02065ef4(obj, param);
    return old;
}
