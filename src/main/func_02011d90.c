/* func_02011d90 @ 0x02011d90, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c1284;
extern void func_02011d28(int *p);
extern int func_02011924(int *p, int p1);
extern void func_020118a0(int *p, int p2);

struct UnkStruct_02011d90 {
    char pad_00[0x250];
    int unk_250;
};

void func_02011d90(struct UnkStruct_02011d90 *p0, int p1, int p2, int p3)
{
    int res;
    func_02011d28(&data_021c1284);
    res = func_02011924(&data_021c1284, p1);
    if (p2 != 0) {
        p0->unk_250 = p3;
    } else if (res != 0) {
        func_020118a0(&data_021c1284, p3);
    }
}
