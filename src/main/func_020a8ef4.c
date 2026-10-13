/* func_020a8ef4 @ 0x020a8ef4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a8ef4 {
    void *vtable;
};

extern void func_02050c84(void *obj);
extern void func_020edb3c(void *obj) __attribute__((arm));

extern unsigned char data_020e3dac[];

void *func_020a8ef4(struct UnkStruct_020a8ef4 *obj)
{
    obj->vtable = (void *) data_020e3dac;
    func_02050c84(obj);
    func_020edb3c(obj);
    return obj;
}
