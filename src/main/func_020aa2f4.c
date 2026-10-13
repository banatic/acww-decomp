/* func_020aa2f4 @ 0x020aa2f4, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ab348(void *p);
extern int func_020ab334(void *p);
extern void func_020ac46c(void *p, int x);
extern void func_020ac71c(void *p);
extern void func_020ac624(void *p);
extern void func_020ac588(void *p);
extern void func_020ac50c(void *p);
extern void func_020ac4ec(void *p);

typedef struct {
    char pad_00[0xc];
    int unk_0C;
    char pad_10[0x84 - 0x10];
    int unk_84;
} UnkStruct_020aa2f4;

void func_020aa2f4(UnkStruct_020aa2f4 *obj)
{
    int r4 = func_020ab348(&obj->unk_84);
    func_020ac46c(&obj->unk_0C, func_020ab334(&obj->unk_84));
    if (r4 == 1) {
        func_020ac71c(&obj->unk_0C);
    } else if (r4 == 2) {
        func_020ac624(&obj->unk_0C);
    } else if (r4 == 3) {
        func_020ac588(&obj->unk_0C);
    } else if (r4 == 4) {
        func_020ac50c(&obj->unk_0C);
    } else if (r4 == 5) {
        func_020ac4ec(&obj->unk_0C);
    }
}
