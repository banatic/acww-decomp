/* func_020b8cc8 @ 0x020b8cc8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e5848;
extern void func_020b91a0(void *);
extern void func_020edb3c(void *);

struct UnkStruct_020b8cc8 {
    void *vtable;
    int unk_04;
    char sub[4];
};

void *func_020b8cc8(struct UnkStruct_020b8cc8 *obj)
{
    obj->vtable = (void *) &data_020e5848;
    func_020b91a0((void *) &obj->sub[0]);
    func_020edb3c((void *) obj);
    return obj;
}
