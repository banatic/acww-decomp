/* func_02039358 @ 0x02039358, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2f4];
    void *array[4];
} UnkStruct_02039358;

extern void func_02039e84(void *ptr);

void func_02039358(UnkStruct_02039358 *a)
{
    int i = 0;
    do {
        if (a->array[i] != 0) {
            func_02039e84(a->array[i]);
        }
        i++;
    } while (i < 4);
}
