/* func_0208a448 @ 0x0208a448, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[20];
} UnkStruct_0208a448;

typedef struct {
    unsigned int vtable;
    char pad_04[8];
    UnkStruct_0208a448 sub1;
    UnkStruct_0208a448 sub2;
    int unk_34;
    int unk_38;
    int unk_3C;
    unsigned char unk_40;
    unsigned char unk_41;
} Obj_t;

extern void func_0208af30(Obj_t *obj);
extern void func_0208a1f8(void *ptr);
extern void func_0208a238(void *, int);
extern char data_020e2058;

Obj_t *func_0208a448(Obj_t *obj, int b)
{
    func_0208af30(obj);
    obj->vtable = (unsigned int) &data_020e2058;
    func_0208a1f8(&obj->sub1);
    func_0208a1f8(&obj->sub2);
    obj->unk_34 = 0;
    obj->unk_38 = 0;
    obj->unk_3C = 0;
    obj->unk_40 = 0;
    obj->unk_41 = (char) b;
    func_0208a238(obj, 0);
    return obj;
}
