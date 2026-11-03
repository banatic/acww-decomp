/* unit_type_info: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203194c @ 0x0203194c, 0x60 bytes, Thumb
 * func_02031930 @ 0x02031930, 0x1c bytes, Thumb
 * func_02031914 @ 0x02031914, 0x1c bytes, Thumb
 */

typedef struct {
    unsigned short value;
    char pad_02[28];
} UnkStruct_02031914;

extern int func_01ffcb2c(int a, int b);
extern unsigned char data_020c9094[];
extern unsigned char data_020c9095[];
extern unsigned char data_020c9096[];
extern unsigned char data_020c9097[];
extern unsigned char data_020c9048[4];
extern struct {
    unsigned short value;
    unsigned char pad[28];
} data_020c907c[];
extern UnkStruct_02031914 data_020c907e[];

int func_0203194c(unsigned char *out, int a, int b)
{
    int idx;
    int off;
    idx = func_01ffcb2c(a, b);
    if (idx < 0x7c) {
        off = idx * 30;
        out[0] = data_020c9094[off];
        out[1] = data_020c9095[off];
        out[2] = data_020c9096[off];
        out[3] = data_020c9097[off];
        return 1;
    } else {
        out[0] = data_020c9048[0];
        out[1] = data_020c9048[1];
        out[2] = data_020c9048[2];
        out[3] = data_020c9048[3];
        return 0;
    }
}

unsigned short func_02031930(int idx)
{
    if (idx < 0x7c) {
        return data_020c907c[idx].value;
    }
    return 0xffff;
}

unsigned short func_02031914(int i)
{
    if (i < 0x7c) {
        return data_020c907e[i].value;
    } else {
        return 0xffff;
    }
}
