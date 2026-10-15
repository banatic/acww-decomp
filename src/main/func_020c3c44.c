/* func_020c3c44 @ 0x020c3c44, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Object {
    void *unk_00;
};

extern char data_020e86ec;
extern void *func_0201615c(struct Object *obj);
extern void func_020edb3c(struct Object *obj);

struct Object *func_020c3c44(struct Object *obj)
{
    obj->unk_00 = &data_020e86ec;
    func_0201615c(obj);
    func_020edb3c(obj);
    return obj;
}
