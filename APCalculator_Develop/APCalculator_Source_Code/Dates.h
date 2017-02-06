#define  JD_OF_J2000	2451545		    /* Julian Date of noon, J2000 */

typedef int		RL_INT4;		/* 4-byte integer */
typedef int		RL_BOOL;		/* boolean */

RL_INT4	Jul_DUTCofJDN(RL_INT4 jd);
RL_INT4	Jul_JDNofDUTC(RL_INT4 dutc);
void Jul_YMDofDUTC(RL_INT4 dutc, RL_INT4 *year, RL_INT4 *month, RL_INT4 *day);
RL_INT4	Jul_DUTCofYMD(RL_INT4 year, RL_INT4 month, RL_INT4 day);
