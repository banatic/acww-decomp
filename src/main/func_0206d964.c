/* func_0206d964 @ 0x0206d964, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct OpaqueType OpaqueType;
extern OpaqueType data_020df1e8;

typedef struct {
    OpaqueType *vtable;
} UnkStruct_0206d964;

extern void *func_020a88ec(UnkStruct_0206d964 *obj);

UnkStruct_0206d964 *func_0206d964(UnkStruct_0206d964 *obj)
{
    func_020a88ec(obj);
    obj->vtable = &data_020df1e8;
    return obj;
}
