/* func_020f28d8 @ 0x020f28d8, 0x34 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    unsigned char unk_04;
} UnkStruct_020f28d8;

extern void func_020f45c4(void *);
extern void func_020f5a3c(int, int);
extern char data_0213ee7c;

UnkStruct_020f28d8 *func_020f28d8(UnkStruct_020f28d8 *p)
{
    func_020f45c4(p);
    p->unk_00 = &data_0213ee7c;
    p->unk_04 = 0x32;
    func_020f5a3c(1, 0x32);
    return p;
}
