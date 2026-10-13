/* func_020464d4 @ 0x020464d4, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6660(void *p);
extern void func_ov003_02224140(int a, int b, int c, int d);
extern void func_ov004_02233ad4(int a, int b, int c, int d);
extern void func_02046490(void *p);

typedef struct {
    unsigned char pad_00;
    unsigned char b1 : 2;
    unsigned char : 0;
    unsigned char : 1;
    unsigned char b2 : 1;
    unsigned char pad_03[5];
    unsigned short unk_08;
    unsigned short unk_0A;
} UnkStruct_020464d4;

void func_020464d4(void *p)
{
    if (func_020b6660(p) != 0) {
        func_ov003_02224140(((UnkStruct_020464d4 *) p)->unk_08 >> 8, ((UnkStruct_020464d4 *) p)->unk_08 & 0xff,
                            ((UnkStruct_020464d4 *) p)->unk_0A, ((UnkStruct_020464d4 *) p)->b1);
        func_02046490(p);
    } else {
        func_ov004_02233ad4(((UnkStruct_020464d4 *) p)->unk_08 >> 8, ((UnkStruct_020464d4 *) p)->unk_08 & 0xff,
                            ((UnkStruct_020464d4 *) p)->unk_0A, ((UnkStruct_020464d4 *) p)->b2);
    }
}
