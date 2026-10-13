/* func_ov138_0229c588 @ 0x0229c588, 0xa8 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_022088ac(int);
extern int func_ov002_0220889c(int);
extern int func_ov002_022088cc(int);
extern int func_ov002_022088bc(int);
extern const unsigned char data_ov138_0229d3e4[];
extern const unsigned char data_ov138_0229d3ec[];
extern const unsigned char data_ov138_0229d3fc[];
extern const unsigned char data_ov138_0229d3f4[];

int func_ov138_0229c588(void *obj, int mode)
{
    unsigned char orig;
    unsigned char *p;

    orig = ((unsigned char *) obj)[0x95];
    if (func_ov002_022088ac(mode)) {
        ((unsigned char *) obj)[0x95] = data_ov138_0229d3e4[((unsigned char *) obj)[0x95]];
    } else if (func_ov002_0220889c(mode)) {
        ((unsigned char *) obj)[0x95] = data_ov138_0229d3ec[((unsigned char *) obj)[0x95]];
    }
    if (orig != ((unsigned char *) obj)[0x95]) {
        return 1;
    }
    if (func_ov002_022088cc(mode)) {
        ((unsigned char *) obj)[0x95] = data_ov138_0229d3fc[((unsigned char *) obj)[0x95]];
    } else if (func_ov002_022088bc(mode)) {
        ((unsigned char *) obj)[0x95] = data_ov138_0229d3f4[((unsigned char *) obj)[0x95]];
    }
    p = ((unsigned char *) obj) + 0x95;
    if (orig == *p) {
        return 0;
    } else {
        return 1;
    }
}
