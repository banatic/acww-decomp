/* func_02021cc8 @ 0x02021cc8, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02021d10(int a, int b);

extern int func_02021ea8(void *self, int *arr, int count, void *predicate);
extern void *func_02015e70(void *arg, void *ptr, int n);

typedef struct {
    char pad[0x100];
    struct UnkStruct_02021cc8 {
        char pad[0x830];
        char *field_0x830;
    } *sub;
} Arg;

void *func_02021cc8(Arg *arg, int a, int b)
{
    void *result;
    result =
        (void *) func_02021ea8((void *) ((void *) arg->sub->field_0x830), (int *) (a), (int) (b), (((void *) func_02021d10)));
    if (result != 0) {
        func_02015e70(arg, (char *) arg->sub->field_0x830 + 0x7dc, 9);
    }
    return result;
}
