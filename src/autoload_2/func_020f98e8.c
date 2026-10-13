/* func_020f98e8 @ 0x020f98e8, 0x60 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_0210b500(int, int);

struct UnkStruct_020f98e8 {
    void *unk_00;
    int unk_04;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    signed char unk_0B;
    signed char unk_0C;
    unsigned short unk_0E;
    signed char unk_10;
};

extern unsigned char data_0213f25c[];

void *func_020f98e8(struct UnkStruct_020f98e8 *r4)
{
    r4->unk_00 = (void *) data_0213f25c;
    r4->unk_04 = 0;
    r4->unk_08 = 0;
    r4->unk_09 = 0;
    r4->unk_0A = 0;
    r4->unk_0B = -1;
    r4->unk_0C = -1;
    r4->unk_0E = 0x78;
    r4->unk_10 = -1;
    func_0210b500(2, -1);
    func_0210b500(1, -1);
    return r4;
}
