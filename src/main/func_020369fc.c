/* func_020369fc @ 0x020369fc, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020372f8(void *, unsigned int);
extern void func_020370f0(void *, int);
extern void func_02036f6c(void *, int);

typedef struct {
    void *unk_00;
    void *unk_04;
    char pad_08[16];
    void *unk_18;
    char pad_1C[8];
    void *unk_24;
} UnkStruct_020369fc;

extern unsigned char data_020da304[];

UnkStruct_020369fc *func_020369fc(UnkStruct_020369fc *param1, int param2)
{
    param1->unk_00 = (void *) data_020da304;
    func_020372f8(&param1->unk_04, param2);
    func_020370f0(&param1->unk_18, param2);
    func_02036f6c(&param1->unk_24, param2);
    return param1;
}
