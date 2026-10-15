/* func_0200d1e4 @ 0x0200d1e4, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0200d1e4 UnkStruct_0200d1e4;
struct UnkStruct_0200d1e4 {
    char data[0x7d4];
    char flag;
    char pad_7D5[0x800 - 0x7d4 - 1];
    int value;
};

extern int data_020ccf94;
extern int func_02073908(int, int);
extern int func_0201100c(UnkStruct_0200d1e4 *);
extern void func_02010f5c(UnkStruct_0200d1e4 *);
extern void func_02010d64(UnkStruct_0200d1e4 *);
extern int func_02010ca4(UnkStruct_0200d1e4 *);
extern void func_0200d2bc(UnkStruct_0200d1e4 *);
extern char func_0200d3a4(UnkStruct_0200d1e4 *);
extern void func_0200ef1c(UnkStruct_0200d1e4 *);
extern void func_0200d258(UnkStruct_0200d1e4 *, char *);

void func_0200d1e4(UnkStruct_0200d1e4 *obj)
{
    char tmp;

    if (func_02073908(data_020ccf94, obj->value)) {
        func_0201100c(obj);
        func_02010f5c(obj);
        func_02010d64(obj);
        func_02010ca4(obj);
        func_0200d2bc(obj);
    } else {
        tmp = func_0200d3a4(obj);
        func_02010f5c(obj);
        func_0200ef1c(obj);
        func_02010ca4(obj);
        func_0200d258(obj, &tmp);
    }
    obj->flag = 0;
}
