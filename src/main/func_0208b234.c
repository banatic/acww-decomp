/* func_0208b234 @ 0x0208b234, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208b234_2 {
    char x;
};

struct UnkStruct_0208b234 {
    char pad_00[0xe0];
    struct UnkStruct_0208b234_2 sub;
    char pad_E1[0x267];
    unsigned char unk_348;
    unsigned char unk_349;
};

extern int func_0208d01c(struct UnkStruct_0208b234_2 *);
extern void func_0208d04c(struct UnkStruct_0208b234_2 *);
extern int func_0208d03c(struct UnkStruct_0208b234_2 *);
extern void func_0208d054(struct UnkStruct_0208b234_2 *);
extern void func_0208b1a0(struct UnkStruct_0208b234 *);
extern void func_0208b344(struct UnkStruct_0208b234 *);
extern void func_02011f48(int);
extern void func_02011f74(int, int);

void func_0208b234(struct UnkStruct_0208b234 *p)
{
    int flag;
    int result;

    if (p->unk_348 != 0 || p->unk_349 != 0) {
        flag = 1;
    } else {
        flag = 0;
    }

    result = func_0208d01c(&p->sub);

    if (flag || result) {
        func_0208d04c(&p->sub);
        if (func_0208d03c(&p->sub) != 0) {
            if (flag) {
                func_0208b1a0(p);
            } else {
                func_02011f48(0);
                func_02011f74(4, 1);
                func_0208b344(p);
            }
        }
    } else {
        func_0208d054(&p->sub);
    }
}
