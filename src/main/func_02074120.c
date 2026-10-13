/* func_02074120 @ 0x02074120, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} Unk028CCF94;

extern Unk028CCF94 *data_020ccf94;
extern int func_02073dd4(Unk028CCF94 *p, int v);
extern void func_020a6f74(int a, int b);

void func_02074120(void)
{
    int value = data_020ccf94->unk_64;
    if (func_02073dd4(data_020ccf94, value) == 0) {
        func_020a6f74(3, 7);
    } else {
        func_020a6f74(value, 7);
    }
}
