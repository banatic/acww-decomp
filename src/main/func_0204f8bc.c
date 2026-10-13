/* func_0204f8bc @ 0x0204f8bc, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char a;
    unsigned char b;
    unsigned char c;
    int d;
    int e;
} UnkStruct_0204f8bc;

extern UnkStruct_0204f8bc data_021c80f4[12];

void func_0204f8bc(void)
{
    unsigned int i = 0;
    goto check;
loop:
    data_021c80f4[i].a = 0xff;
    data_021c80f4[i].b = 0;
    data_021c80f4[i].c = 0;
    data_021c80f4[i].d = 0;
    data_021c80f4[i].e = 0;
    i++;
check:
    if (i < 12) {
        goto loop;
    }
}
