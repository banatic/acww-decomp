/* func_020f35ac @ 0x020f35ac, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213eb3c;
extern void func_020f4514(void *obj);
extern void func_020edb3c(void *obj);

typedef struct {
    void *vt;
} UnkStruct_020f35ac;

UnkStruct_020f35ac *func_020f35ac(UnkStruct_020f35ac *obj)
{
    obj->vt = &data_0213eb3c;
    func_020f4514(obj);
    func_020edb3c(obj);
    return obj;
}
