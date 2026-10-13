/* func_02083800 @ 0x02083800, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int *func_0208385c(unsigned int, unsigned int);

typedef struct {
    int unk_00;
    unsigned int count;
} Header;

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
} Entry;

unsigned int *func_02083800(Header *h, unsigned int idx)
{
    unsigned int *result = 0;
    if (idx < h->count) {
        Entry *arr = (Entry *) ((char *) func_0208385c(h->count, 0) + 8);
        result = &arr[idx].unk_04;
    }
    return result;
}
