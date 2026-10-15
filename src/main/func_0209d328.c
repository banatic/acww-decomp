/* func_0209d328 @ 0x0209d328, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02055cf4(void *);

typedef struct {
    unsigned char flag;
    unsigned int value;
    char sub[1];
} UnkStruct_0209d328;

UnkStruct_0209d328 *func_0209d328(UnkStruct_0209d328 *obj)
{
    func_02055cf4(obj->sub);
    obj->flag = 0;
    obj->value = 0;
    return obj;
}
