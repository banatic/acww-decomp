/* func_02048ab0 @ 0x02048ab0, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x20];
    int f20 : 5;
    int bit5 : 1;
    int pad2 : 26;
} UnkStruct_02048ab0;
extern unsigned char data_021c7a08[];
extern void func_02048bc0(void *a, void *b, int j, int i, int k);
void func_02048ab0(void *a, void *b, int c, int d)
{
    int j;
    int i;
    int j0 = 0;
    for (i = 0; i < d; i++) {
        for (j = j0; j < c; j++) {
            UnkStruct_02048ab0 *e = (UnkStruct_02048ab0 *) (data_021c7a08 + j * 0x90 + i * 0x24);
            if (e->bit5 == 0) {
                func_02048bc0(a, b, j + 1, i + 1, 2);
            }
        }
    }
}
