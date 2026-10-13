/* func_02043cdc @ 0x02043cdc, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6660(void);
extern void func_02043b40(void *obj, void *data);
extern void func_02043a70(void *obj, void *data);

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} UnkStruct_02043cdc;

void func_02043cdc(void *obj, UnkStruct_02043cdc *src)
{
    if (func_020b6660()) {
        UnkStruct_02043cdc temp;
        temp.unk_00 = src->unk_00;
        temp.unk_04 = src->unk_04;
        func_02043b40(obj, &temp);
    } else {
        UnkStruct_02043cdc temp;
        temp.unk_00 = src->unk_00;
        temp.unk_04 = src->unk_04;
        func_02043a70(obj, &temp);
    }
}
