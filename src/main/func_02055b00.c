/* func_02055b00 @ 0x02055b00, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020dd10c[];
extern void func_020ba01c(void *);

typedef struct {
    char *data;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    char sub[0x1C];
    char unk_30;
    char unk_31;
} UnkStruct_02055b00;

UnkStruct_02055b00 *func_02055b00(UnkStruct_02055b00 *ptr)
{
    ptr->data = data_020dd10c;
    func_020ba01c(ptr->sub);
    ptr->unk_04 = 0;
    ptr->unk_08 = 0;
    ptr->unk_0C = 0;
    ptr->unk_10 = 0;
    ptr->unk_30 = 0;
    ptr->unk_31 = 0;
    return ptr;
}
