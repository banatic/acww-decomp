/* func_020835a8 @ 0x020835a8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e1ac8;
extern void func_02083654(void);
extern void func_02083c78(void *obj);
extern void func_020edb3c(void *obj);
extern void func_02138c48(void *obj, int a, int b, void (*cb)(void));

typedef struct {
    void *vtable;
    int unk_04;
    char sub_obj[4];
} Object;

void *func_020835a8(Object *obj)
{
    obj->vtable = &data_020e1ac8;
    func_02138c48(&obj->sub_obj, 5, 8, func_02083654);
    func_02083c78(obj);
    func_020edb3c(obj);
    return obj;
}
