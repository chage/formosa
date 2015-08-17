#ifndef _BBS_PERM_H
#define _BBS_PERM_H

#define CHECK_PERM(ulevelbits, x)	((ulevelbits == x) ? 1 : 0)

#define PERM_DEFAULT     0
#define PERM_NORMAL      50
#define PERM_CHAT        20
#define PERM_PAGE        1
#define PERM_POST        10
#define PERM_BM          100
#define PERM_CLOAK       255
#define PERM_SYSOP       255

#if defined(NSYSUBBS1) || defined(NSYSUBBS2) || defined(NSYSUBBS3)
# undef PERM_CHAT
# undef PERM_PAGE
# define PERM_CHAT        20
# define PERM_PAGE        20
#endif


#if 0
#define CHECK_PERM(ulevelbits, x)	( (x) ? ulevelbits&(x) : 1)

#define PERM_CHAT        00000001  /*  'C' �i�ϥβ�ѫ� */
#define PERM_TALK        00000002  /*  'T' �i�ϥ����H��ͥ\�� */
#define PERM_POST        00000004  /*  'P' �i�i�K�G�i */
#define PERM_EMAIL       00000008  /*  'E' �i�H�e email */
#define PERM_POSTNEWS    00000010  /*  'N' �G�i�i�e�W���� */
#define PERM_CHATIGNORE  00000020  /*  'D' �i�ϥβ�ѫǽ�H�\�� */
#define PERM_CLOAK       00000040  /*  'O' �i���� */
#define PERM_XEMPT       00000080  /*  'X' �b���ä[�O�d */
#define PERM_MESSAGE     00000100  /*  'M' �i�ϥΰe�T���\�� */
#define PERM_NOIDLEOUT   00000200  /*  'L' ���Q IDLE OUT */

#define PERM_LOGINOK     00010000
#define PERM_CHECKID     00020000  /*  'I' �w�q�L�����{�� */
#define PERM_BM          00040000  /*  'B' �O�D */
#define PERM_SYSOP       00080000  /*  'S' ���� */

#define PERM_DEFAULT	(PERM_CHAT|PERM_TALK|PERM_POST)
#endif


#endif	/* _BBS_PERM_H */
