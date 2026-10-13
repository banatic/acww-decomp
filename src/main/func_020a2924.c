/* func_020a2924 @ 0x020a2924, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void *);
extern int func_02098fd0(int, int);
extern int func_020ec260(int);
extern void func_02074294(int);

struct UnkStruct_020a2924 {
    char pad_00[0xa1];
    char unk_A1;
};

void func_020a2924(struct UnkStruct_020a2924 *s)
{
    func_02074294(func_020ec260(func_02098fd0(func_020984e8(s), 2)));
    s->unk_A1 = 0;
}
