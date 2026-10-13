/* func_ov003_02234d70 @ 0x02234d70, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02234d70;
extern UnkStruct_02234d70 *data_020ccf94;
extern int func_ov003_02233e4c(void *a, void *b);
extern int func_02073dd4(void *a, int b);
extern void func_ov003_02234cf0(void *a, void *b);
extern void func_ov068_0226fe28(void *a, void *b);

int func_ov003_02234d70(void *self)
{
    int t[3];
    int r = func_ov003_02233e4c(self, t);
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64)) {
        func_ov003_02234cf0(self, t);
    } else {
        func_ov068_0226fe28(self, t);
    }
    return r;
}
