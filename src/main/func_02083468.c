/* func_02083468 @ 0x02083468, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *data;
    int pad_04;
    char buffer;
} UnkStruct_02083468;

extern char data_020e1a90;
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void *));
extern void func_02083c78(void *obj);
extern void func_020edb3c(void *obj);
extern int func_02083514(void *);

void *func_02083468(void *obj_ptr)
{
    UnkStruct_02083468 *obj = (UnkStruct_02083468 *) obj_ptr;
    obj->data = &data_020e1a90;
    __cxa_vec_cleanup((void *) (&obj->buffer), 5, 2, (((void (*)(void *)) func_02083514)));
    func_02083c78(obj);
    func_020edb3c(obj);
    return obj;
}
