/* func_ov118_0229b390 @ 0x0229b390, 0x1e bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa1];
    unsigned char a1;
    unsigned char a2;
} UnkStruct_0229b390;

extern int func_ov118_0229a460(UnkStruct_0229b390 *p, int n);

unsigned char func_ov118_0229b390(UnkStruct_0229b390 *p)
{
    if (func_ov118_0229a460(p, 1)) {
        return p->a2;
    } else {
        return p->a1;
    }
}
