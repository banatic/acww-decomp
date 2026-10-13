/* func_02089b80 @ 0x02089b80, 0x3a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x44];
    unsigned int f0;
    unsigned int f1;
    unsigned int f2;
} DestStruct;

typedef struct {
    unsigned int f0;
    unsigned int f1;
    unsigned int f2;
} SrcStruct;

extern void func_02089c20(DestStruct *dest, int a, int b, int c, int d, int e, int f, unsigned char g, int h);

void func_02089b80(DestStruct *dest, int param1, SrcStruct *src, int param3, int param4, int param5, int param6, int param7,
                   unsigned char param8, int param9)
{
    func_02089c20(dest, param1, param3, param4, param5, param6, param7, param8, param9);
    dest->f0 = src->f0;
    dest->f1 = src->f1;
    dest->f2 = src->f2;
}
