/* func_ov002_02208620 @ 0x02208620, 0x4c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02208620 {
    unsigned char pad_00[0xc];
    int unk_0C;
    int unk_10;
    int unk_14;
} UnkStruct_02208620;

extern int func_ov002_022087ec(UnkStruct_02208620 *obj, int val);
extern void func_02001b7c(int);
extern void func_02001bb4(int);
extern void func_ov002_02208348(UnkStruct_02208620 *obj, int val);

void func_ov002_02208620(UnkStruct_02208620 *obj, int flag)
{
    obj->unk_0C = obj->unk_10 - func_ov002_022087ec(obj, obj->unk_10);
    if (obj->unk_0C > obj->unk_14) {
        switch (flag) {
            case 0:
                func_02001b7c(1);
                func_ov002_02208348(obj, 2);
                break;
            case 1:
                func_02001bb4(1);
                func_ov002_02208348(obj, 0);
                break;
        }
    }
}
