/* func_ov147_0229a200 @ 0x0229a200, 0x38 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ee660(void *);
extern void *func_ov147_02299ae8(void *);
extern void func_ov147_0229a6f0(void *);
extern void *func_020b9cfc(void *);

extern unsigned char data_020da13c[];
extern unsigned char data_ov147_0229aa28[];

void *func_ov147_0229a200(void *this)
{
    func_020ee660(this);
    *(unsigned int *) this = (unsigned int) data_020da13c;
    *(unsigned int *) this = (unsigned int) data_ov147_0229aa28;
    func_ov147_02299ae8((char *) this + 0x54);
    func_ov147_0229a6f0((char *) this + 0xb0);
    func_020b9cfc((char *) this + 0xd0);
    return this;
}
