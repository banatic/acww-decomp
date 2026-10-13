/* func_02002e54 @ 0x02002e54, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned short w[32];
} Data_020d5ca4;

extern Data_020d5ca4 data_020d5ca4;
extern void DC_FlushRange(void *ptr, int len);
extern void G3X_SetToonTable(void *ptr);

void func_02002e54(void)
{
    Data_020d5ca4 local;
    unsigned short *p;
    unsigned short v;

    local = data_020d5ca4;
    DC_FlushRange(&local, 0x40);
    p = (unsigned short *) 0x04000060;
    v = *p;
    v &= ~0x3002;
    *p = v;
    G3X_SetToonTable(&local);
}
