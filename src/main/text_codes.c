/* text_codes: 14 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02050c78 @ 0x02050c78, 0xa bytes, Thumb
 * func_02050c58 @ 0x02050c58, 0x20 bytes, Thumb
 * func_02050c50 @ 0x02050c50, 0x8 bytes, Thumb
 * func_02050c48 @ 0x02050c48, 0x8 bytes, Thumb
 * func_02050c40 @ 0x02050c40, 0x8 bytes, Thumb
 * func_02050c38 @ 0x02050c38, 0x8 bytes, Thumb
 * func_02050c30 @ 0x02050c30, 0x8 bytes, Thumb
 * func_02050c28 @ 0x02050c28, 0x8 bytes, Thumb
 * func_02050c20 @ 0x02050c20, 0x8 bytes, Thumb
 * func_02050c18 @ 0x02050c18, 0x8 bytes, Thumb
 * func_02050c10 @ 0x02050c10, 0x8 bytes, Thumb
 * func_02050c04 @ 0x02050c04, 0xc bytes, Thumb
 * func_02050bf8 @ 0x02050bf8, 0xc bytes, Thumb
 * func_02050be0 @ 0x02050be0, 0x12 bytes, Thumb
 */

typedef struct {
    unsigned short key;
    unsigned short value;
} Entry;

extern int data_020cb8f8;
extern int data_020cb8fc;
extern int data_020cb910;
extern int data_020cb904;
extern int data_020cb900;
extern int data_020cb908;
extern int data_020cb914;
extern int data_020cb90c;
extern int data_020cb8f0;
extern struct UnkStruct_02050c04 {
    int unk_00;
    int unk_04;
} data_020cb9bc[];
extern struct UnkStruct_02050bf8 {
    int unk_00;
    int unk_04;
} data_020cba34[];

int func_02050c78(unsigned char *p, int v)
{
    p[0] = (unsigned char) v;
    p[1] = (unsigned char) (v >> 8);
    return 2;
}

unsigned short func_02050c58(void *param1, void *param2)
{
    unsigned short result;
    signed char c1;
    signed char c2;
    unsigned int val;
    unsigned int val2;
    unsigned int val3;

    c1 = *(signed char *) param2;
    c2 = *(signed char *) ((char *) param2 + 1);
    val = (unsigned int) c1 & 0xff;
    val2 = ((unsigned int) c2 << 8) & 0x0000ff00;
    val3 = val | val2;
    result = (unsigned short) val3;
    *(unsigned short *) param1 = result;
    return 2;
}

int func_02050c50(void)
{
    return (int) &data_020cb8f8;
}

int func_02050c48(void)
{
    return (int) &data_020cb8fc;
}

int func_02050c40(void)
{
    return (int) &data_020cb910;
}

int func_02050c38(void)
{
    return (int) &data_020cb904;
}

int func_02050c30(void)
{
    return (int) &data_020cb900;
}

int func_02050c28(void)
{
    return (int) &data_020cb908;
}

int func_02050c20(void)
{
    return (int) &data_020cb914;
}

int func_02050c18(void)
{
    return (int) &data_020cb90c;
}

int func_02050c10(void)
{
    return (int) &data_020cb8f0;
}

struct UnkStruct_02050c04 *func_02050c04(int index)
{
    return &data_020cb9bc[index];
}

struct UnkStruct_02050bf8 *func_02050bf8(int index)
{
    return &data_020cba34[index];
}

unsigned short func_02050be0(unsigned short key, unsigned short cur_key, Entry *e)
{
    while (1) {
        if (key == cur_key) {
            return e->value;
        }
        e++;
        cur_key = e->key;
        if (cur_key == 0) {
            break;
        }
    }
    return key;
}
