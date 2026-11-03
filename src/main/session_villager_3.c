/* session_villager_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02078478 @ 0x02078478, 0x38 bytes, Thumb
 * func_02078460 @ 0x02078460, 0x18 bytes, Thumb
 */

typedef struct {
    unsigned short pad_00;
    unsigned char unk_02;
} UnkStruct_02078460;

extern void *data_020ccf94;
extern int func_02073d90(void *);
extern int func_0207f294(int);
extern int func_0207cf74(int);
extern void func_020784b0(int, int);
extern void func_020778b0(void *a, unsigned short b, void *c);

void func_02078478(int a, int b)
{
    if (func_02073d90(data_020ccf94)) {
        int v = func_0207f294(a);
        if (func_0207cf74(v)) {
            func_020784b0(v, b);
        }
    }
}

void func_02078460(UnkStruct_02078460 *a, unsigned char b, unsigned short *c)
{
    unsigned short val = *c;
    func_020778b0(a, val, c);
    a->unk_02 = b;
}
