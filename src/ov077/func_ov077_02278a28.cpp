/* func_ov077_02278a28 @ 0x02278a28, 0x2c bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02278a28 {
    int pad_00;
} UnkStruct_02278a28;

typedef struct MainObj {
    void *vptr;
    char pad_04[0x658 - 4];
    UnkStruct_02278a28 sub;
} MainObj;

extern "C" void func_ov077_02278d4c(UnkStruct_02278a28 *);
extern "C" void func_0202ee5c(MainObj *);
extern "C" void __attribute__((arm)) func_020edf54(MainObj *);
extern int data_ov077_0227988c;

extern "C" MainObj *func_ov077_02278a28(MainObj *obj)
{
    obj->vptr = &data_ov077_0227988c;
    func_ov077_02278d4c(&obj->sub);
    func_0202ee5c(obj);
    func_020edf54(obj);
    return obj;
}
