/* func_ov066_02269934 @ 0x02269934, 0x48 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    char pad_00[0xb4];
    int (*func)(void);
} UnkStruct_02269934;

extern UnkStruct_02269934 *data_ov066_0226bdf4;

int func_ov066_02269934(void)
{
    int (*fn)(void);
    UnkStruct_02269934 *obj = data_ov066_0226bdf4;

    if (obj != 0 && (fn = obj->func) != 0) {
        return fn();
    }
    return 0;
}
