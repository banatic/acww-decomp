/* func_020f3c84 @ 0x020f3c84, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f3f14(void *p);
extern void func_020edb3c(void *p);
extern int data_0213ec40;

struct UnkStruct_020f3c84 {
    int *data;
};

struct UnkStruct_020f3c84 *func_020f3c84(struct UnkStruct_020f3c84 *obj)
{
    obj->data = &data_0213ec40;
    func_020f3f14(obj);
    func_020edb3c(obj);
    return obj;
}
