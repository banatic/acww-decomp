/* func_02021b08 @ 0x02021b08, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02021b08 {
    unsigned char pad_00[0x830];
    int value;
};

struct UnkStruct_02021b08_2 {
    unsigned char pad_00[0x100];
    struct UnkStruct_02021b08 *inner;
};

extern int func_02021b48(void);

extern int func_02021ea8(void *self, int *arr, int count, void *predicate);
extern int func_02081d64(int v);
extern void *func_02015e70(struct UnkStruct_02021b08_2 *self, int a, int b);

int func_02021b08(struct UnkStruct_02021b08_2 *self, int a1, int a2)
{
    int ret;

    ret = func_02021ea8((void *) (self->inner->value), (int *) (a1), (int) (a2), (((void *) func_02021b48)));
    if (ret != 0) {
        int x = func_02081d64(ret);
        func_02015e70(self, x, 9);
    }
    return ret;
}
