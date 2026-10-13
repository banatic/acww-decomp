/* func_02094f7c @ 0x02094f7c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a88ec(void *obj);
extern int data_020e2f54;

typedef struct {
    void *vtbl;
} UnkStruct_02094f7c;

void *func_02094f7c(void *obj)
{
    func_020a88ec(obj);
    ((UnkStruct_02094f7c *) obj)->vtbl = &data_020e2f54;
    return obj;
}
