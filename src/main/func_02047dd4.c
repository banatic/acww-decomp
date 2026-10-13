/* func_02047dd4 @ 0x02047dd4, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct UnkStruct_02047dd4 {
    unsigned char pad_00[3];
    unsigned char unk_03;
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
    unsigned char unk_07;
} UnkStruct_02047dd4;

extern int func_0204cb90(char *p1, int p2, char *p3, UnkStruct_02047dd4 *p4);
extern int func_0209e380(char *p, UnkStruct_02047dd4 *p2);
extern int func_0209dcdc(char *p1, char *p2, char *p3);

int func_02047dd4(int arg1, int arg2, UnkStruct_02047dd4 *a3, UnkStruct_02047dd4 *a4, int a5, int a6, char *a7)
{
    char local1[8];
    char local2[3];
    int result;

    if (a5 != 0) {
        char *b7 = a7;
        if (func_0204cb90(b7 + 0x17254, arg2, b7, a4) < 0) {
            if (a6 != 0) {
                return 1;
            }

            *(unsigned int *) &local1 = 0;
            *((unsigned int *) &local1 + 1) = 0;
            *(unsigned int *) &local1 = 0;
            *((unsigned int *) &local1 + 1) = 0;

            ((unsigned char *) &local1)[5] = a4->unk_05;
            ((unsigned char *) &local1)[4] = a3->unk_07;
            ((unsigned char *) &local1)[3] = a3->unk_06;

            result = func_0209e380(local1, a4) + 1;
            return result;
        } else {
            local2[2] = a4->unk_05;
            local2[1] = a4->unk_04;
            local2[0] = a4->unk_03;

            result = func_0209dcdc(local2, a7 + 0x172a8, a7);
            if (result >= 0) {
                return result;
            }
            return 0;
        }
    }
    return 1;
}
