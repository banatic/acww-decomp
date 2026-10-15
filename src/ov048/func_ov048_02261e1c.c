/* func_ov048_02261e1c @ 0x02261e1c, 0x40 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x813 - 0x44];
    char unk_813;
} UnkStruct_02261e1c;

extern void func_ov048_02261d08(UnkStruct_02261e1c *p);
extern unsigned char func_ov048_022609fc(void *receiver);
extern void func_0206844c(int a, char *b, int c);
extern int data_ov048_02263d20;

void func_ov048_02261e1c(UnkStruct_02261e1c *p, int mode)
{
    if (mode == 1) {
        p->unk_813 = 2;
        func_ov048_02261d08(p);
    } else if (mode == 2) {
        char c = func_ov048_022609fc(p);
        func_0206844c(p->unk_40, &c, data_ov048_02263d20);
    }
}
