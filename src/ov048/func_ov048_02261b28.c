/* func_ov048_02261b28 @ 0x02261b28, 0x2c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_ov048_022609fc(void *receiver);
extern void func_0206844c(int, char *, int);
extern int data_ov048_02263d20;

typedef struct {
    char pad_00[0x40];
    int unk_40;
} UnkStruct_02261b28;

void func_ov048_02261b28(UnkStruct_02261b28 *obj, int arg1)
{
    if (arg1 == 1) {
        char c = func_ov048_022609fc(obj);
        func_0206844c(obj->unk_40, &c, data_ov048_02263d20);
    }
}
