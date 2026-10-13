/* func_ov118_0229b630 @ 0x0229b630, 0x34 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229b630 {
    unsigned char pad_00[0xa0];
    unsigned char count;
} UnkStruct_0229b630;

char *func_ov118_0229b630(UnkStruct_0229b630 *p)
{
    if (p->count >= 13) {
        return (char *) p + 0x60c;
    }
    p->count++;
    return (char *) p + 0xfc + 0x6c * (p->count - 1);
}
