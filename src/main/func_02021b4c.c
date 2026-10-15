/* func_02021b4c @ 0x02021b4c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02021b4c {
    char pad_00[0x830];
    int value;
} UnkStruct_02021b4c;

typedef struct UnkStruct_02021b4c_2 {
    char pad_00[0x100];
    UnkStruct_02021b4c *ptr;
} UnkStruct_02021b4c_2;

extern int func_02021b8c(int a, int b);

extern int func_02021ea8(void *self, int *arr, int count, void *predicate);
extern int func_02081d64(int);
extern void *func_02015e70(void *a, int b, int c);

int func_02021b4c(UnkStruct_02021b4c_2 *a, int b, int c)
{
    int result = func_02021ea8((void *) (a->ptr->value), (int *) (b), (int) (c), (((void *) func_02021b8c)));
    if (result != 0) {
        func_02015e70(a, func_02081d64(result), 9);
    }
    return result;
}
