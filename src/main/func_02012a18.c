/* func_02012a18 @ 0x02012a18, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0204f61c(void *s, unsigned int x, unsigned int y, unsigned int z);
extern void *data_021c80bc;

typedef struct {
    int unk_00;
    char pad_04[4];
    int unk_08;
} UnkStruct_02012a18;

int func_02012a18(void *unused, UnkStruct_02012a18 *p)
{
    void *g = data_021c80bc;
    int result = 0;
    unsigned int x, y;
    if (g == 0) {
        goto done;
    }
    x = (unsigned int) (p->unk_00 >> 17);
    y = (unsigned int) (p->unk_08 >> 17);
    if (func_0204f61c(g, x, y, 0x200) == 0) {
        goto done;
    }
    result = 1;
done:
    return result;
}
