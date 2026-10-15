/* func_ov147_02299ae8 @ 0x02299ae8, 0x18 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02066a30(void *p);
extern char data_ov147_0229aae4[];

void *func_ov147_02299ae8(void *p)
{
    func_02066a30(p);
    *(void **) p = data_ov147_0229aae4;
    return p;
}
