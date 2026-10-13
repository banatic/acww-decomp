/* func_ov143_02299a64 @ 0x02299a64, 0x38 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x9f];
    volatile unsigned char idx;
} func_ov143_02299a64_Struct;

void *func_ov143_02299a64(func_ov143_02299a64_Struct *obj)
{
    if (obj->idx >= 16) {
        return (void *) ((char *) obj + 0x930);
    } else {
        obj->idx = obj->idx + 1;
        return (void *) ((char *) obj + 0x2dc + ((obj->idx - 1) * 0x6c));
    }
}
