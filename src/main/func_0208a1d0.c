/* func_0208a1d0 @ 0x0208a1d0, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208a1d0 {
    int value;
    char pad_04[8];
};
struct UnkStruct_0208a1d0_2 {
    struct UnkStruct_0208a1d0 *array;
};
struct UnkStruct_0208a1d0_3 {
    struct UnkStruct_0208a1d0_2 *inner;
    int index;
};

int func_0208a1d0(struct UnkStruct_0208a1d0_3 *arg)
{
    return arg->inner->array[arg->index].value;
}
