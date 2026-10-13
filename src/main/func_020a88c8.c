/* func_020a88c8 @ 0x020a88c8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9b44(void *ptr);
extern char data_020e3d7c[];
extern char data_020da6c4[];

typedef struct {
    void *vtbl;
    char sub[1];
} Object;

void *func_020a88c8(Object *obj)
{
    obj->vtbl = data_020e3d7c;
    func_020a9b44(&obj->sub);
    obj->vtbl = data_020da6c4;
    return obj;
}
