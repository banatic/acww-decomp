/* func_ov106_0229dc04 @ 0x0229dc04, 0x7c bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229dc04 {
    char pad_00[0x3fb4];
    unsigned char unk_3FB4;
} UnkStruct_0229dc04;

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;

extern int func_0206f56c(void);
extern int func_ov002_02208054(UnkStruct_0229dc04 *obj, int x);
extern int func_ov002_0220a784(void *ptr, int x);
extern void func_ov106_0229d3bc(UnkStruct_0229dc04 *obj);
extern void func_ov106_0229d6c4(UnkStruct_0229dc04 *obj);
extern void func_ov106_0229d3e8(UnkStruct_0229dc04 *obj);

void func_ov106_0229dc04(UnkStruct_0229dc04 *obj)
{
    int v;

    if (func_0206f56c()) {
        func_ov106_0229d3bc(obj);
    }
    if (func_ov002_02208054(obj, 1)) {
        func_ov106_0229d6c4(obj);
        return;
    }
    if (data_021fbdd8 != 0 && data_021fbddc != 0) {
        v = 1;
    } else {
        v = 0;
    }
    if (v != 0) {
        if (func_ov002_0220a784(&obj->unk_3FB4, 3)) {
            func_ov106_0229d3e8(obj);
            return;
        }
        if (func_ov002_0220a784(&obj->unk_3FB4, 4)) {
            func_ov106_0229d3bc(obj);
        }
    }
}
