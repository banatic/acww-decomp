/* func_02090968 @ 0x02090968, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02090a2c(void *);

typedef struct {
    int unk_00;
    char pad_04[4];
    char unk_08;
    char pad_09[15];
} UnkStruct_02090968;

typedef struct {
    char unk_00;
    char pad_01[3];
    UnkStruct_02090968 elems[32];
} UnkStruct_02090968_2;

void func_02090968(UnkStruct_02090968_2 *out)
{
    UnkStruct_02090968 *p = out->elems;
    int i = 0;
    int val = i;
    int sentinel = i;
    for (; i < 32; p++, i++) {
        if (p->unk_00 != ~sentinel) {
            p->unk_08 = (char) val;
            func_02090a2c(p);
            out->unk_00 = (char) i;
        }
    }
}
