/* func_02077afc @ 0x02077afc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e9968(void *heap, int size, int type);

extern unsigned char data_021c9b30[];

int func_02077afc(int size, int type)
{
    void *r0;
    int r1;
    int r2;
    int r3;

    r3 = size;
    r2 = type;
    r0 = *(void **) data_021c9b30;
    r1 = r3;
    r3 = 0x020e9968;
    return func_020e9968(r0, r1, r2);
}
