/* func_ov070_02278a28 @ 0x02278a28, 0x2c bytes, Thumb, module ov070
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

extern "C" void *func_ov070_022796c0(UnkStruct_02278a28 *);
extern "C" void *func_0202ee5c(MainObj *);
extern "C" void __attribute__((arm)) func_020edf54(MainObj *);
extern int data_ov070_02279e4c;

extern "C" MainObj *func_ov070_02278a28(MainObj *obj)
{
    obj->vptr = &data_ov070_02279e4c;
    func_ov070_022796c0(&obj->sub);
    func_0202ee5c(obj);
    func_020edf54(obj);
    return obj;
}
