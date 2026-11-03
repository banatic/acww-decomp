/* mes_bg_3: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020acb94 @ 0x020acb94, 0x34 bytes, Thumb
 * func_020acb70 @ 0x020acb70, 0x24 bytes, Thumb
 * func_020acb48 @ 0x020acb48, 0x28 bytes, Thumb
 */

struct Object {
    void *vtbl;
    char pad_04[0x0C];
    char sub[16];
};

extern void func_0208af30(void *);
extern void *func_0208ec40(void *, int);
extern void func_0208ea6c(void *, int);
extern int data_020e4014;
extern void *func_0208ec14(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *arg);

void *func_020acb94(void *obj)
{
    func_0208af30(obj);
    *(unsigned int *) obj = (unsigned int) &data_020e4014;
    ((unsigned int *) obj)[3] = 0x800;
    func_0208ec40((char *) obj + 0x10, 1);
    func_0208ea6c((char *) obj + 0x10, 0);
    return obj;
}

void *func_020acb70(void *self)
{
    *(void **) self = ((char *) &data_020e4014);
    func_0208ec14((char *) self + 0x10);
    func_0208af00(self);
    return self;
}

struct Object *func_020acb48(struct Object *obj)
{
    obj->vtbl = &data_020e4014;
    func_0208ec14(obj->sub);
    func_0208af00(obj);
    func_020edb3c(obj);
    return obj;
}
