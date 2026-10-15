/* func_ov002_02207f6c @ 0x02207f6c, 0x14 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e993c(void *a1, void *a2);

extern unsigned char data_021c9b28[];

void func_ov002_02207f6c(void *a1)
{
    void *v1 = a1;
    void *v2 = *(void **) data_021c9b28;
    func_020e993c(v2, v1);
}
