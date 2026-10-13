/* func_0204d594 @ 0x0204d594, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020e9948(void *heap, int size);

struct UnkStruct_0204d594 {
    char pad_00[0x54];
    int *array;
    int count;
};

void func_0204d594(struct UnkStruct_0204d594 *self, void *heap)
{
    int i;

    if (self->count > 0) {
        self->array = func_020e9948(heap, self->count * 4);
        if (self->array) {
            i = 0;
            for (; i < self->count; i++) {
                self->array[i] = 0;
            }
        }
    }
}
