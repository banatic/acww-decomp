/* func_0208a198 @ 0x0208a198, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[10];
    short value;
} Elem;

typedef struct {
    Elem *array;
} UnkStruct_0208a198;

typedef struct {
    UnkStruct_0208a198 *a;
    int default_index;
} Param;

short func_0208a198(Param *param, int index)
{
    int idx = index;
    if (idx < 0) {
        idx = param->default_index;
    }
    return (param->a->array + idx)->value;
}
