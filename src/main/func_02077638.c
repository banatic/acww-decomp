/* func_02077638 @ 0x02077638, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct {
    unsigned char opcode;
    unsigned short length;
    unsigned char tmp[3];
} UnkStruct_02077638;

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern void (*data_020ccfa0[256])(void *, unsigned short);

void func_02077638(unsigned char *p, unsigned int remaining)
{
    UnkStruct_02077638 t;
    unsigned short length;
    unsigned char opcode;

    while (remaining != 0) {
        MI_CpuCopy8(p, t.tmp, 3);
        p += 3;
        remaining -= 3;
        MI_CpuCopy8(t.tmp, &t.length, 2);
        MI_CpuCopy8(&t.tmp[2], &t.opcode, 1);
        length = t.length;
        opcode = t.opcode;
        data_020ccfa0[opcode](p, length);
        p += length;
        remaining -= length;
    }
}
