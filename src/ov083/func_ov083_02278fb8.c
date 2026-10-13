/* func_ov083_02278fb8 @ 0x02278fb8, 0x30 bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x65c];
    void *unk_65C;
} UnkStruct_02278fb8;

extern int func_0202edc8(UnkStruct_02278fb8 *p);
extern void func_0201c280(UnkStruct_02278fb8 *p, void *q);
extern void func_ov083_02278d20(void *q, UnkStruct_02278fb8 *p);

int func_ov083_02278fb8(UnkStruct_02278fb8 *p)
{
    if (func_0202edc8(p) == 0) {
        return 0;
    }
    func_0201c280(p, &p->unk_65C);
    func_ov083_02278d20(&p->unk_65C, p);
    return 1;
}
