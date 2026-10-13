/* func_020904ac @ 0x020904ac, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02055124(void *);
extern void func_02056ffc(void *);
extern int func_02056f94(void *);

typedef struct {
    char pad_00[8];
    unsigned int unk_08;
    char pad_0C[0xc];
    unsigned int *unk_18;
    char pad_1C[4];
} Slot;

typedef struct {
    unsigned int active;
    char pad_04[0x20];
    char sub_24[0x9c];
    char sub_C0[0x1c];
    unsigned int flags[3];
    Slot slots[3];
} UnkStruct_020904ac;

void func_020904ac(UnkStruct_020904ac *obj)
{
    int i;
    if (obj->active != 0) {
        func_02055124(obj->sub_24);
        for (i = 1; i < 3; i++) {
            if (obj->flags[i] != 0) {
                func_02056ffc(&obj->slots[i]);
                *obj->slots[i].unk_18 = obj->slots[i].unk_08;
            }
        }
        if (func_02056f94(obj->sub_C0) != 0) {
            obj->active = 0;
        }
    }
}
