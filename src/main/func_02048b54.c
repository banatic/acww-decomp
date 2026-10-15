/* func_02048b54 @ 0x02048b54, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02048bc0(int, int, int, int, int);
extern int func_020644cc(int);
struct UnkStruct_02048b54 {
    char pad_00[0x20];
    unsigned int : 3;
    signed int flag : 1;
};
struct UnkStruct_02048b54_2 {
    struct UnkStruct_02048b54 arr[4];
};
extern struct UnkStruct_02048b54_2 data_021c7a08[];
void func_02048b54(int p0, int p1, int p2, int p3)
{
    int i;
    int start = 0;
    int flag = 0;
    for (i = 0; i < p2; i++) {
        int found = 1;
        int j = start;
        while (j < p3) {
            if (data_021c7a08[i].arr[j].flag) {
                found = flag;
                break;
            }
            j++;
        }

        if (found) {
            int sum = func_020644cc(p3) + 1;
            func_02048bc0(p0, p1, i + 1, sum, 1);
        }
    }
}
