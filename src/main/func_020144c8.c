/* func_020144c8 @ 0x020144c8, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[6];
    short unk_06;
    char pad1[2];
    char unk_0A;
} UnkStruct_020144c8;

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad1[0x4d4];
} UnkStruct_020144c8_2;

extern unsigned short data_020c80f8;
extern int func_02019e00(char *ptr);
extern int func_02019de8(char *ptr);
extern int func_02019d0c(char *ptr, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern void func_02014718(UnkStruct_020144c8 *p1, UnkStruct_020144c8_2 *p2);

void func_020144c8(UnkStruct_020144c8 *p1, UnkStruct_020144c8_2 *p2)
{
    if (p1->unk_06 == p2->unk_8E && func_02019e00((char *) p2 + 0x564) == 3 && func_02019de8((char *) p2 + 0x564) != 0) {
        func_02019d0c((char *) p2 + 0x564, 0, 2, 0, 0, 0, 0, 0, 0, (int) (unsigned short) data_020c80f8, 0);
        func_02014718(p1, p2);
        p1->unk_0A = 1;
    }
}
