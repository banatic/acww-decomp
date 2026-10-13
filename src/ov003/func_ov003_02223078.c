/* func_ov003_02223078 @ 0x02223078, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02044878(int);
struct UnkStruct_02223078 {
    char pad_00[0x5c];
    int unk_5C;
};
extern struct UnkStruct_02223078 *func_020961a8(void *);
int func_ov003_02223078(int a, int *b)
{
    int result = 0;
    struct UnkStruct_02223078 *obj;
    obj = func_020961a8(func_02044878(a));
    if (obj != 0) {
        if (obj->unk_5C < *b) {
            result = 1;
        }
    }
    return result;
}
