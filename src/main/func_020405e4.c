/* func_020405e4 @ 0x020405e4, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern void *func_020992e4(int);

struct UnkStruct_020405e4 {
    unsigned char pad_00[8];
    unsigned int unk_08;
};

void func_020405e4(struct UnkStruct_020405e4 *a, unsigned char *b)
{
    void *ptr;

    if (!func_020984e8()) {
        return;
    }
    ptr = func_020992e4(func_020984e8());
    if (!ptr) {
        return;
    }

    b[3] = ((unsigned char *) ptr)[1];
    b[2] = ((unsigned char *) ptr)[0];
    b[1] = (unsigned char) a->unk_08;
}
