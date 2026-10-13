/* func_020ab71c @ 0x020ab71c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

/* FAKEMATCH: the single-pass do/while keeps the key pointer loaded before the buffer address; the plain call loads it last */

extern void func_02064328(void *dest, const void *src1, const void *src2, unsigned int count);
extern void func_020ab83c(void *a, void *b, void *c, void *d);
extern unsigned char data_020e40a4[];
extern unsigned char data_020e40a8[];
typedef struct {
    int unk_00;
    unsigned int unk_04;
    char unk_08[0x5c];
    char unk_64;
} UnkStruct_020ab71c;
void func_020ab71c(UnkStruct_020ab71c *p)
{
    char buf[0x40];
    unsigned char *ptr;
    int val;
    UnkStruct_020ab71c *ptr2;
    val = 0 != 0U;
    ptr = data_020e40a4;
    do {
        ptr2 = p;
    } while (val);
    func_02064328(buf, data_020e40a8, ptr, p->unk_04);
    func_020ab83c(&ptr2->unk_08, buf, ptr2, &p->unk_64);
}
