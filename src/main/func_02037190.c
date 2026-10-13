/* func_02037190 @ 0x02037190, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xe];
    unsigned char flag;
} UnkStruct_02037190;

extern void func_02035624(int);

void func_02037190(UnkStruct_02037190 *s)
{
    if (s->flag) {
        func_02035624(27);
        s->flag = 0;
    }
}
