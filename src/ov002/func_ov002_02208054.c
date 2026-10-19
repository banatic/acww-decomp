/* func_ov002_02208054 @ 0x02208054, 0x3c bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206fe7c(void);
extern void func_0200467c(int);

struct UnkStruct_02208054 {
    unsigned short pad_00; // offset 0
    unsigned short val;    // offset 2
};
extern struct UnkStruct_02208054 data_021fbe40;

int func_ov002_02208054(int unused, int p)
{
    int masked;
    masked = data_021fbe40.val & 0xFFF;
    if (masked) {
        func_0206fe7c();
        func_0200467c(0x866);
        if (p != 0) {
            func_0200467c(0x3B);
        }
        return 1;
    } else {
        return 0;
    }
}
