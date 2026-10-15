/* func_02092644 @ 0x02092644, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x34];
    int id;
    unsigned char pad_38[8];
} UnkStruct_02092644;

extern int func_02034270(UnkStruct_02092644 *p, int a, int b, int c);
extern void func_0203423c(UnkStruct_02092644 *p);
extern int func_020ba4e4(void);
extern int func_020b6598(void);
extern int func_02094b58(int p1, int p2, int p3, int p4, int p5, char *p6);
extern int func_02094cf8(int p1, int p2, int p3, int p4, int p5, int p6);
extern char data_020e2864[];
extern char data_020e285c[];

int func_02092644(int a, int b, int c, int d)
{
    UnkStruct_02092644 st;
    int id;
    int result;

    func_02034270(&st, b, 0, 0);
    id = st.id;
    result = 3;

    if ((id == 0x16) || (func_020ba4e4() == 1)) {
        if (func_02094b58(0x85, a, b, c, d, data_020e2864) == 0) {
            result = 2;
        }
    } else if ((id == 3) && (func_020b6598() != 0)) {
        if (func_02094b58(0x86, a, b, c, d, data_020e285c) == 0) {
            result = 2;
        }
    } else if (id == 0x13) {
        result = func_02094cf8(0x84, a, b, c, d, 0);
    } else {
        result = func_02094cf8(0x83, a, b, c, d, 0);
    }

    func_0203423c(&st);
    return result;
}