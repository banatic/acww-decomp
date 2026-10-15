/* func_0206dd48 @ 0x0206dd48, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020df258;
typedef struct {
    void *unk_00;
} Obj_t;
extern void func_0206dcec(Obj_t *);
extern void *func_020a8c38(Obj_t *);
extern void func_020edb3c(Obj_t *);

Obj_t *func_0206dd48(Obj_t *obj)
{
    obj->unk_00 = &data_020df258;
    func_0206dcec(obj);
    func_020a8c38(obj);
    func_020edb3c(obj);
    return obj;
}
