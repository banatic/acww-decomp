/* func_020a6ce4 @ 0x020a6ce4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a6ce4 {
    char pad_00[0x64];
    int unk_64;
};

extern struct UnkStruct_020a6ce4 *data_020ccf94;
extern int data_021f4320[];

extern int func_02073dd4(struct UnkStruct_020a6ce4 *p, int field);
extern int func_020a6284(int *p);
extern void func_020a7064(int);
extern void func_020a6280(int *p, int val);
extern void func_020a6288(int *p, int val);

void func_020a6ce4(void)
{
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        int idx = func_020a6284(data_021f4320);
        if (idx < 4) {
            func_020a7064(idx);
            func_020a6280(data_021f4320, idx);
            func_020a6288(data_021f4320, 4);
        }
    }
}
