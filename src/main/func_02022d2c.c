/* func_02022d2c @ 0x02022d2c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02022d2c {
    char pad_830[0x830];
    int value;
} UnkStruct_02022d2c;

typedef struct UnkStruct_02022d2c_2 {
    char pad_100[0x100];
    UnkStruct_02022d2c *inner;
} UnkStruct_02022d2c_2;

extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202da38(UnkStruct_02022d2c_2 *, char *, char *, int, int, int, int, int, int);
extern struct {
    int a;
    unsigned char b;
} data_020c8d70;

int func_02022d2c(UnkStruct_02022d2c_2 *param)
{
    func_0202da38(param, (char *) param + 0x104, (char *) param + 0x122, 0x1e,
                  func_020036e8(func_0208150c(param->inner->value)), data_020c8d70.a, data_020c8d70.b, 0, 0);
    return 1;
}
