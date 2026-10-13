/* func_ov003_02226a40 @ 0x02226a40, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x14];
    int unk_14;
} UnkStruct_02226a40;
extern void *data_ov003_0223cf74;
int func_ov003_02227118(void *self, int k);
int func_020555a4(void *p, int k, void *g, int d, int e, int f, int h);

int func_ov003_02226a40(char *self, UnkStruct_02226a40 *a, int *b, int c)
{
    int k = func_ov003_02227118(self, 5);
    return func_020555a4(self + 0xf78, k, data_ov003_0223cf74, a->unk_14, *b, c, 1) != 0 ? 1 : 0;
}
