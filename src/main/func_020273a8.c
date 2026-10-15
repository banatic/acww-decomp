/* func_020273a8 @ 0x020273a8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_02099734(int);
extern int func_0202d754(int);
extern void func_0201579c(int, int, int);
extern int func_02015828(int, int);

typedef struct {
    int unk_00;
    int unk_04;
} DataPair;

extern void func_0202dbf0(int, DataPair);
extern DataPair data_020d9488;

void func_020273a8(int param, int event)
{
    int tmp;

    tmp = func_0202d754(func_02099734(func_020984e8()));
    func_0201579c(param, tmp, 1);
    func_02015828(param, 5);
    func_0202dbf0(param, data_020d9488);
}
