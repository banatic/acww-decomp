/* func_02034b04 @ 0x02034b04, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern char data_021c5174[];

void *func_ov004_02232104(void *a, void *b, void *c);
void func_02034bd4(void *a, void *b, unsigned int c, void *d);

void *func_02034b04(unsigned short *src, void *p1, void *p2, unsigned int flag)
{
    unsigned short local;
    unsigned int cond;

    local = *src;
    cond = (data_020e54a8 == 1);
    if (cond > 0) {
        void *result;
        result = func_ov004_02232104(&local, p1, p2);
        if (flag != 0) {
            func_02034bd4(&local, p1, 0, p2);
        }
        return result;
    } else {
        return data_021c5174;
    }
}
