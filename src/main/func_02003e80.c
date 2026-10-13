/* func_02003e80 @ 0x02003e80, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02003e80 {
    int pad_00;
    void *(*func)(void *);
};

struct UnkStruct_02003e80_2 {
    struct UnkStruct_02003e80 *inner;
};

void *func_02003e80(struct UnkStruct_02003e80_2 *self)
{
    return self->inner->func(self);
}
