/* func_02032180 @ 0x02032180, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02032180 UnkStruct_02032180;
struct UnkStruct_02032180 {
    char pad_00[0x2c];
    UnkStruct_02032180 *next;
};

extern UnkStruct_02032180 *data_021c30e4;
extern void func_020325b8(UnkStruct_02032180 *);

int func_02032180(UnkStruct_02032180 *target)
{
    UnkStruct_02032180 *cur = data_021c30e4;
    UnkStruct_02032180 *prev = 0;
    while (cur != 0) {
        if (cur == target) {
            if (prev) {
                prev->next = cur->next;
            } else {
                data_021c30e4 = cur->next;
            }
            func_020325b8(target);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}
