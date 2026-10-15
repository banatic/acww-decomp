/* func_0203e904 @ 0x0203e904, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203e904;
extern int func_0203ef90(int arg);
extern int func_02095d84(void);
extern int func_0203eb08(struct UnkStruct_0203e904 *s);
extern int func_02095904(void);

struct UnkStruct_0203e904 {
    char pad_00[12];
    int unk_0C;
    char pad_10[7];
    unsigned char unk_17;
};

int func_0203e904(struct UnkStruct_0203e904 *s)
{
    if ((func_0203ef90(s->unk_0C), func_02095d84()) == 0) {
        return 0;
    }
    s->unk_17 = 1;
    if (func_0203eb08(s) != 0) {
        func_02095904();
        return 1;
    } else {
        return 0;
    }
}
