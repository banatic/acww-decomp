/* func_020a9cf8 @ 0x020a9cf8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020a9cf8 UnkStruct_020a9cf8;
typedef struct Vtable Vtable;

struct Vtable {
    int (*unk_00)();
    int (*unk_04)();
    int (*unk_08)();
    int (*unk_0C)();
    int (*unk_10)();
    int (*unk_14)(UnkStruct_020a9cf8 *);
};

struct UnkStruct_020a9cf8 {
    Vtable *vtable;
};

int func_020a9cf8(UnkStruct_020a9cf8 **param)
{
    UnkStruct_020a9cf8 *obj;
    int result = 0;
    obj = *param;
    if (obj) {
        result = obj->vtable->unk_14(obj);
    }
    return result;
}
