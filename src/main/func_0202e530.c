/* func_0202e530 @ 0x0202e530, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_02003618(int, int);

typedef struct {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0202e530;

void func_0202e530(UnkStruct_0202e530 *s, int arg2)
{
    if (s->unk_830) {
        func_02003618(func_0208150c(s->unk_830), arg2);
    }
}
