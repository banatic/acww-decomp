/* func_02071568 @ 0x02071568, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x2c4];
} UnkStruct_02071568;
typedef struct {
    char data[0x38];
} UnkStruct_02071568_2;
extern int data_021d054c[8][8];
extern UnkStruct_02071568 *data_021d0484;
extern UnkStruct_02071568_2 *data_021d047c;
extern char data_021dc7bc;
extern void func_02098844(void *p, int i);
extern int func_020996b8(void);
extern int func_02072bd0(int a, int b);
extern void func_0203cff8(UnkStruct_02071568 *p, int val);
extern int func_0203cfc8(UnkStruct_02071568 *p);
extern void func_020577c8(UnkStruct_02071568_2 *p, int a1, int a2, int a3, int a4, int a5, int a6);

int func_02071568(int a, int b)
{
    int i = (unsigned char) (a & 7);
    int level;
    int j = (unsigned char) (b & 7);
    int value = data_021d054c[i][j];

    if (value != 0 && data_021d0484 != 0 && data_021d047c != 0) {
        func_02098844(&data_021dc7bc, i);
        level = func_02072bd0(func_020996b8(), j);
        func_0203cff8(&data_021d0484[j], level);
        func_020577c8(&data_021d047c[j], value, 0, 0, func_0203cfc8(&data_021d0484[j]), 0, 0);
        return 1;
    }
    return 0;
}
