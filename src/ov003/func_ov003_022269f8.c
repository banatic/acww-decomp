/* func_ov003_022269f8 @ 0x022269f8, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x14];
    int unk_14;
} UnkStruct_022269f8;
extern void *data_ov003_0223cf74;
int func_ov003_022270d8(void *self, int k);
int func_020555a4(void *p, int k, void *g, int d, int e, int f, int h);

int func_ov003_022269f8(char *self, UnkStruct_022269f8 *a, int *b, int c)
{
    int k = func_ov003_022270d8(self, 5);
    return func_020555a4(self + 0x14f4, k, data_ov003_0223cf74, a->unk_14, *b, c, 1) != 0 ? 1 : 0;
}
