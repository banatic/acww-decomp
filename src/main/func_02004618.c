/* func_02004618 @ 0x02004618, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02004618;
typedef struct VTable {
    unsigned char pad_00[0x1c];
    int (*method)(struct UnkStruct_02004618 *, int);
} VTable;

typedef struct UnkStruct_02004618 {
    VTable *vtable;
} UnkStruct_02004618;

extern UnkStruct_02004618 *data_0213fff0;

int func_02004618(int arg)
{
    return data_0213fff0->vtable->method(data_0213fff0, arg);
}
