/* func_0202feb4 @ 0x0202feb4, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020da18c;
extern void func_0202fc18(void *a, int b, int c, int d, int e);

typedef struct {
    void *unk_00;
} Object;

Object *func_0202feb4(Object *obj, int b, int c, int d, int e)
{
    obj->unk_00 = &data_020da18c;
    func_0202fc18(obj, b, c, d, e);
    return obj;
}
