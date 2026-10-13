/* func_0209a77c @ 0x0209a77c, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc];
    char unk_0C[0x10];
    char arr[5][30];
    unsigned char b2;
    unsigned char b3;
    unsigned char b4;
    unsigned char b5;
    unsigned char b6;
    unsigned char b7;
    unsigned char b8;
    unsigned char b9;
    unsigned char ba;
} UnkStruct_0209a77c;

extern void func_0209bd5c(UnkStruct_0209a77c *p);
extern void func_02003738(char *p);
extern void func_02095238(char *p);

void func_0209a77c(UnkStruct_0209a77c *p)
{
    int i;
    func_0209bd5c(p);
    func_02003738(p->unk_0C);
    for (i = 0; i < 5; i++) {
        func_02095238(p->arr[i]);
    }
    p->b2 = 1;
    p->b3 = 1;
    p->b4 = 0;
    p->b5 = 0;
    p->b6 = 1;
    p->b7 = 1;
    p->b8 = 0;
    p->b9 = 0;
    p->ba = 5;
}
