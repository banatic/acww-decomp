/* func_ov118_0229a474 @ 0x0229a474, 0x44 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void func_02004668(int, int);

typedef struct {
    unsigned char bytes[3];
} Triple;

typedef struct {
    unsigned char pad_00[0xa9];
    unsigned char type;
    unsigned char pad_AA[0x47ad - 0xaa];
    Triple arr[256];
} UnkStruct_0229a474;

void func_ov118_0229a474(UnkStruct_0229a474 *p, int a1)
{
    int val;
    if (p->type == 14) {
        return;
    }
    val = (p->arr[p->type].bytes[0] - 0x18) * 2 - 0x7f;
    if (val < -127) {
        val = -127;
    } else if (val > 128) {
        val = 128;
    }
    func_02004668(a1, val);
}
