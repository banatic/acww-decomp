/* func_0208a160 @ 0x0208a160, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Elem {
    int a;
    int b;
    int c;
} Elem;

typedef struct UnkStruct_0208a160 {
    Elem *arr;
    int count;
} UnkStruct_0208a160;

typedef struct UnkStruct_0208a160_2 {
    UnkStruct_0208a160 *inner;
    int index;
    int value;
    int pad_0C;
    int type;
} UnkStruct_0208a160_2;

int func_0208a160(UnkStruct_0208a160_2 *self)
{
    int result = 0;
    UnkStruct_0208a160 *inner;
    int idx;
    int val;
    int shifted;
    Elem *arr;

    if (self->type == 1) {
        inner = self->inner;
        idx = self->index;
        if (idx >= inner->count - 1) {
            val = self->value;
            shifted = val >> 12;
            arr = inner->arr;
            if (shifted >= arr[idx].b - 1) {
                result = 1;
            }
        }
    }
    return result;
}
