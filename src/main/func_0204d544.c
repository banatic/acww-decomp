/* func_0204d544 @ 0x0204d544, 0x4e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e993c(void *data, void *item);

typedef struct {
    char pad_00[0x54];
    void **array;
    int count;
} UnkStruct_0204d544;

void func_0204d544(UnkStruct_0204d544 *list, void *arg1)
{
    if (list->array != 0 && list->count > 0) {
        int i = 0;
        int zero = 0;
        for (; i < list->count; i++) {
            if (list->array[i] != 0) {
                func_020e993c(arg1, list->array[i]);
                list->array[i] = (void *) zero;
            }
        }
        func_020e993c(arg1, list->array);
        list->array = 0;
        list->count = 0;
    }
}
