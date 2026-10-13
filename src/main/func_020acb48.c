/* func_020acb48 @ 0x020acb48, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e4014;
extern void func_0208ec14(void *arg);
extern void func_0208af00(void *arg);
extern void func_020edb3c(void *arg);

struct Object {
    void *vtbl;
    char pad_04[0x0C];
    char sub[16];
};

struct Object *func_020acb48(struct Object *obj)
{
    obj->vtbl = &data_020e4014;
    func_0208ec14(obj->sub);
    func_0208af00(obj);
    func_020edb3c(obj);
    return obj;
}
