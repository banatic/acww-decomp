/* func_020b55b8 @ 0x020b55b8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c38(void *);

struct UnkStruct_020b55b8 {
    void *ptr;
};

extern unsigned char data_020e51d0[];

struct UnkStruct_020b55b8 *func_020b55b8(struct UnkStruct_020b55b8 *obj)
{
    obj->ptr = (void *) data_020e51d0;
    func_020a8c38(obj);
    return obj;
}
