/* func_02032658 @ 0x02032658, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02032658 UnkStruct_02032658;
struct UnkStruct_02032658 {
    char pad_00[0x38];
    UnkStruct_02032658 *next;
};

extern UnkStruct_02032658 *data_021c30e0;
extern void func_02032758(UnkStruct_02032658 *);

int func_02032658(UnkStruct_02032658 *target)
{
    UnkStruct_02032658 *cur = data_021c30e0;
    UnkStruct_02032658 *prev = 0;
    while (cur != 0) {
        if (cur == target) {
            if (prev) {
                prev->next = cur->next;
            } else {
                data_021c30e0 = cur->next;
            }
            func_02032758(target);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}
