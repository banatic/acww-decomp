/* talk_object_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02067504 @ 0x02067504, 0x3c bytes, Thumb
 * func_020674d8 @ 0x020674d8, 0x2c bytes, Thumb
 */

typedef struct VTable {
    char pad_00[0x18];
    void (*callback)(void *, int);
} VTable;

typedef struct UnkStruct_02067504 {
    char pad_00[0x31c];
    void *unk_31C;
    char pad_320[0x14a8 - 0x320];
    void *unk_14A8;
    char pad_14AC[0x1e96 - 0x14ac];
    unsigned char flag;
} UnkStruct_02067504;

extern int func_020ab4c8(void *);
extern int func_020a829c(unsigned char *);
extern int func_020a8298(int);
extern void func_0200467c(unsigned short);
extern unsigned short data_020cce84[];

void func_02067504(UnkStruct_02067504 *obj)
{
    if (obj->flag) {
        int result;
        void *ptr;
        VTable *vt;

        result = func_020a829c((unsigned char *) func_020ab4c8((void *) &obj->unk_31C));
        ptr = obj->unk_14A8;
        vt = (VTable *) (*(void **) ptr);
        vt->callback(ptr, result);
        obj->flag = 0;
    }
}

void func_020674d8(int arg)
{
    int ret;
    unsigned short cmd;

    ret = func_020a8298(arg + 0x14ac);
    if (ret < 2) {
        cmd = data_020cce84[ret];
        if (cmd != 0) {
            func_0200467c(cmd);
        }
    }
}
