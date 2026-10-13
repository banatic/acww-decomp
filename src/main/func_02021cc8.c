/* func_02021cc8 @ 0x02021cc8, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02021ea8(void *c, int a, int b, void (*func)(void));
extern void func_02015e70(void *arg, void *ptr, int n);
extern void func_02021d10(void);

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
    result = func_02021ea8((void *) arg->sub->field_0x830, a, b, func_02021d10);
    if (result != 0) {
        func_02015e70(arg, (char *) arg->sub->field_0x830 + 0x7dc, 9);
    }
    return result;
}
