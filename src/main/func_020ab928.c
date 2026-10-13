/* func_020ab928 @ 0x020ab928, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020ab928 {
    void *vtable;
};

extern void func_020a9a40(void *);
extern void func_020edb3c(void *);

extern unsigned char data_020e3fcc[];

struct UnkStruct_020ab928 *func_020ab928(struct UnkStruct_020ab928 *obj)
{
    obj->vtable = (void *) data_020e3fcc;
    func_020a9a40(obj);
    func_020edb3c(obj);
    return obj;
}
