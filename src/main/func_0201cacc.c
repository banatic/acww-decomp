/* func_0201cacc @ 0x0201cacc, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x48];
    unsigned char state;
} UnkStruct_0201cacc;

extern int func_0201cb68(UnkStruct_0201cacc *obj, int arg);
extern void func_0201cb54(UnkStruct_0201cacc *obj, int arg);
extern void func_0201cb40(UnkStruct_0201cacc *obj, int arg);

void func_0201cacc(UnkStruct_0201cacc *obj, int arg)
{
    if (func_0201cb68(obj, arg)) {
        if (obj->state == 0) {
            func_0201cb54(obj, arg);
        } else if (obj->state == 0x14) {
            func_0201cb40(obj, arg);
        }
        obj->state++;
        if (obj->state >= 0x28) {
            obj->state = 0;
        }
    }
}
