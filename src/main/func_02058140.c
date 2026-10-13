/* func_02058140 @ 0x02058140, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02059674(void *ptr, int val);

typedef struct {
    unsigned char pad_00[0xD4];
    unsigned char unk_D4;
    unsigned char unk_D5;
    unsigned short hword_D6;
} Func02058140;

void func_02058140(Func02058140 *ptr)
{
    func_02059674(ptr, 1);
    ptr->hword_D6 = 0;
    ptr->unk_D4 = 0;
}
