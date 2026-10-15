/* func_020b4cd8 @ 0x020b4cd8, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int strcmp(int a, void *b);

typedef struct {
    char pad_00[0x24];
    void *unk_24;
} func_020b4cd8_param;

int func_020b4cd8(func_020b4cd8_param *param)
{
    void *q = *(void **) ((char *) param->unk_24 + 0x18f0);
    int r = (*(int (**)(void *))((char *) *(void **) q + 0xc))(q);
    return strcmp(r, (char *) param->unk_24 + 0xafc) != 0;
}
