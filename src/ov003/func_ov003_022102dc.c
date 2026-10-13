/* func_ov003_022102dc @ 0x022102dc, 0x78 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022102dc {
    unsigned char pad_00[0x5a0];
    int sub;
    unsigned char pad_5A4[0x24c];
    int unk_7F0;
    unsigned char pad_7F4[8];
    int unk_7FC;
    int unk_800;
};

extern int data_020ccf94;
extern int func_02073908(int, int);
extern int func_0203e168(void);
extern int func_02008258(struct UnkStruct_022102dc *, int);
extern void func_0200d4e8(struct UnkStruct_022102dc *, int, int, int);
extern void func_020ba35c(int);
extern void func_020109a0(struct UnkStruct_022102dc *, int, int, int);
extern void func_0205eae0(int *, int, int, int);

void func_ov003_022102dc(struct UnkStruct_022102dc *a)
{
    if (func_02073908(data_020ccf94, a->unk_800) != 0 && func_0203e168() == 0) {
        a->unk_7FC = func_02008258(a, a->unk_7F0);
        func_0200d4e8(a, 3, 1, -1);
        return;
    }
    func_020ba35c(a->unk_800);
    func_020109a0(a, 0x5f, 3, 0);
    func_0205eae0(&a->sub, 0x22, 3, 1);
}
