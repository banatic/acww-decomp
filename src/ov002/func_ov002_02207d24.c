/* func_ov002_02207d24 @ 0x02207d24, 0x36 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xcc];
    unsigned char unk_CC;
    unsigned char pad_CD;
    unsigned char unk_CE;
} UnkStruct_02207d24;

extern int func_0208a844(UnkStruct_02207d24 *obj);
extern void func_ov002_02207cf0(UnkStruct_02207d24 *obj, int flag);

int func_ov002_02207d24(UnkStruct_02207d24 *obj, int flag)
{
    obj->unk_CE = 0;
    if (flag) {
        func_ov002_02207cf0(obj, flag);
    }
    if (func_0208a844(obj) == 0) {
        obj->unk_CC = 0;
        return 1;
    } else {
        obj->unk_CC = 4;
        return 0;
    }
}
