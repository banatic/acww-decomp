/* func_ov144_0229aabc @ 0x0229aabc, 0x64 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

typedef struct Obj_ov144_0229b3f8 Obj_ov144_0229b3f8;
extern int func_ov002_02208014(void *receiver);
extern int func_ov002_02208008(Obj_ov144_0229b3f8 *);
extern int func_ov144_022996d4(Obj_ov144_0229b3f8 *, int);
extern unsigned char *func_ov144_0229a824(Obj_ov144_0229b3f8 *);
extern void func_ov144_0229a12c(Obj_ov144_0229b3f8 *);
extern void func_ov144_0229a0c8(Obj_ov144_0229b3f8 *);
extern void func_ov144_0229a17c(Obj_ov144_0229b3f8 *);
extern void func_ov144_0229a798(Obj_ov144_0229b3f8 *);

struct FlagsStruct {
    char pad_00[2];
    unsigned short flags;
};
extern struct FlagsStruct data_021fbe40;

void func_ov144_0229aabc(Obj_ov144_0229b3f8 *obj)
{
    if (func_ov002_02208014(obj)) {
        func_ov144_0229a824(obj);
        return;
    }
    if (func_ov144_022996d4(obj, func_ov002_02208008(obj))) {
        func_ov144_0229a12c(obj);
        return;
    }
    if (data_021fbe40.flags & 1) {
        func_ov144_0229a0c8(obj);
        return;
    }
    if (data_021fbe40.flags & 2) {
        func_ov144_0229a17c(obj);
        func_ov144_0229a798(obj);
    }
}
