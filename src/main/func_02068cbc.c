/* func_02068cbc @ 0x02068cbc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a234(void *);

typedef struct {
    char pad_00[0xC];
    char data[0x70];
    int unk_7C;
} UnkStruct_02068cbc;

int func_02068cbc(UnkStruct_02068cbc *p)
{
    if (p->unk_7C == 0) {
        if (func_0208a234(p->data) == 0) {
            return 1;
        }
    }
    return 0;
}
