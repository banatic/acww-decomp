/* func_0206dd08 @ 0x0206dd08, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02002e04(void *arg);
extern int func_02002dc8(void *arg);

typedef struct {
    char pad_00[0x68];
    unsigned short unk_68;
    unsigned char unk_6A;
    unsigned char unk_6B;
    unsigned char unk_6C;
} UnkStruct_0206dd08;

void func_0206dd08(UnkStruct_0206dd08 *p, unsigned short val, void *arg)
{
    p->unk_68 = val;
    p->unk_6C = 0;
    p->unk_6B = !func_02002e04(arg);
    p->unk_6A = func_02002dc8(arg);
}
