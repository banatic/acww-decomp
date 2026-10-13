/* func_ov003_0221cd5c @ 0x0221cd5c, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x02d8];
    unsigned int arr[6];
} UnkStruct_0221cd5c;

int func_ov003_0221cd5c(UnkStruct_0221cd5c *p)
{
    unsigned int i;
    for (i = 0; i < 6; i++) {
        p->arr[i] = 0;
    }
    return 1;
}
