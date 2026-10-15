/* func_0208e024 @ 0x0208e024, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8cac(void *);
extern void func_020a8c1c(void *);
extern char data_020e21e4;

typedef struct {
    void *vtable;
} UnkStruct_0208e024;

void *func_0208e024(UnkStruct_0208e024 *obj)
{
    func_020a8cac(obj);
    obj->vtable = &data_020e21e4;
    func_020a8c1c(obj);
    return obj;
}
