/* func_ov077_02278dd4 @ 0x02278dd4, 0x3c bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8858(void *);
extern void func_0206844c(int, char *, int);
extern int func_020155cc(void *);
extern void func_ov077_02278e10(void *, int);
extern int data_ov077_02279700;

void func_ov077_02278dd4(char *this)
{
    char c;

    if (func_020e8858((char *) this + 0xb4) == 0) {
        c = 0x10;
        func_0206844c(*(int *) ((char *) this + 0x40), &c, data_ov077_02279700);
        func_020155cc(this);
        func_ov077_02278e10(this, 0);
    }
}
