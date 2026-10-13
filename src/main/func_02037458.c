/* func_02037458 @ 0x02037458, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x18];
    int counter;
} UnkStruct_02037458;

int func_02037458(UnkStruct_02037458 *obj)
{
    int res = 0;
    if (obj->counter > 0) {
        obj->counter--;
        if (obj->counter <= 0) {
            res = 1;
        }
    }
    return res;
}
