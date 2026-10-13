/* func_02036f48 @ 0x02036f48, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02036f48 {
    void *vtable;
};

extern void func_020edb3c(struct UnkStruct_02036f48 *obj);

extern unsigned char data_020da2e4[];

struct UnkStruct_02036f48 *func_02036f48(struct UnkStruct_02036f48 *obj)
{
    obj->vtable = (void *) data_020da2e4;
    func_020edb3c(obj);
    return obj;
}
