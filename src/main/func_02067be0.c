/* func_02067be0 @ 0x02067be0, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206841c(void *);
extern void func_02067c04(void *);

void func_02067be0(void *param)
{
    void *obj;
    void *vtable;
    void (*func)(void *);

    func_0206841c(param);
    func_02067c04(param);
    obj = *(void **) ((char *) param + 0x14a8);
    vtable = *(void **) obj;
    func = *(void (**)(void *))((char *) vtable + 0x74);
    func(obj);
}
