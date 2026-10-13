/* func_0202decc @ 0x0202decc, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020161ac(void *p);
extern char data_020d9df8;

typedef struct {
    void *unk_00;
    char pad_04[288];
    unsigned short unk_124;
    char pad_126[118];
    unsigned short unk_19C;
} UnkStruct_0202decc;

void *func_0202decc(UnkStruct_0202decc *ptr)
{
    func_020161ac(ptr);
    ptr->unk_00 = &data_020d9df8;
    ptr->unk_124 = 0xfff1;
    ptr->unk_19C = 0xfff1;
    return ptr;
}
