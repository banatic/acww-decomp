/* func_ov002_02208418 @ 0x02208418, 0x40 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220882c(void *, unsigned int);

void func_ov002_02208418(void *object, int denominator, unsigned char direction, int word)
{
    int result;
    *(unsigned char *) ((char *) object + 0x18) = direction;
    *(int *) ((char *) object + 0x14) = word;
    func_ov002_0220882c(object, (unsigned int) denominator);
    *(int *) ((char *) object + 0xc) = 0;
    result = *(unsigned char *) ((char *) object + 0x18);
    switch (result) {
        case 0:
        case 1:
            result = 0xc0;
            *(int *) ((char *) object + 0x10) = result;
            break;
        case 2:
        case 3:
            result = 0x100;
            *(int *) ((char *) object + 0x10) = result;
            break;
    }
}
