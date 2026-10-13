/* func_0208fd88 @ 0x0208fd88, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208af30(void *);
extern int data_020e23e4;

struct UnkStruct_0208fd88 {
    void *unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    short unk_10;
    char unk_12;
    char unk_13;
    int unk_14;
    int unk_18;
    int unk_1C;
    char unk_20;
};

struct UnkStruct_0208fd88 *func_0208fd88(struct UnkStruct_0208fd88 *arg)
{
    func_0208af30(arg);
    arg->unk_00 = &data_020e23e4;
    arg->unk_0C = 0;
    arg->unk_10 = 0;
    arg->unk_12 = 0;
    arg->unk_13 = 0;
    arg->unk_14 = 0;
    arg->unk_18 = 0;
    arg->unk_1C = 0;
    arg->unk_20 = 0;
    return arg;
}
