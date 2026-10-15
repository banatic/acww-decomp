/* func_ov090_02299774 @ 0x02299774, 0x4c bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x38];
} UnkStruct_02299774;
typedef struct {
    char pad_00;
} OtherObj;
typedef struct {
    void *vtable;
    char pad_04[0x9c - 4];
    UnkStruct_02299774 subs[3];
    char pad_144[0x1164 - 0x144];
    OtherObj other;
} Obj_ov090_02299820;

extern void *func_ov002_02207f80(unsigned int);
extern void *func_ov002_0220830c(void *);
extern void *func_020b9af4(UnkStruct_02299774 *);
extern void *func_ov002_0220ba24(OtherObj *);
extern char data_ov090_02299820[];

Obj_ov090_02299820 *func_ov090_02299774(void)
{
    Obj_ov090_02299820 *obj;
    UnkStruct_02299774 *p;
    obj = (Obj_ov090_02299820 *) func_ov002_02207f80(0x1280);
    if (obj) {
        func_ov002_0220830c(obj);
        obj->vtable = data_ov090_02299820;
        p = &obj->subs[0];
        do {
            func_020b9af4(p);
            p++;
        } while (p != &obj->subs[3]);
        func_ov002_0220ba24(&obj->other);
    }
    return obj;
}
