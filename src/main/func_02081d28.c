/* func_02081d28 @ 0x02081d28, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern __arm int memcmp(const void *, const void *, unsigned int);
extern int func_0209518c(void *, void *);

typedef struct {
    unsigned short unk_00;
    char data[12];
} UnkStruct_02081d28;

int func_02081d28(UnkStruct_02081d28 *a, UnkStruct_02081d28 *b)
{
    if (a->unk_00 != b->unk_00) {
        goto fail;
    }
    if (memcmp((char *) a + 2, (char *) b + 2, 0xc) != 0) {
        goto fail;
    }
    if (func_0209518c(a, b) == 0) {
        goto fail;
    }
    return 1;
fail:
    return 0;
}
