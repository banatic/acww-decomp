/* func_0208a1b0 @ 0x0208a1b0, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Elem {
    char pad_00[8];
    short value;
    char pad_0A[2];
} Elem;

typedef struct UnkStruct_0208a1b0_2 {
    void *array;
} UnkStruct_0208a1b0_2;

typedef struct UnkStruct_0208a1b0 {
    void *b;
    int default_index;
} UnkStruct_0208a1b0;

short func_0208a1b0(UnkStruct_0208a1b0 *a0, int index)
{
    UnkStruct_0208a1b0_2 *b;
    Elem *arr;
    if (index < 0) {
        index = a0->default_index;
    }
    b = a0->b;
    arr = b->array;
    return arr[index].value;
}
