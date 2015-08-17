
#ifndef _BBS_CONFIG_H_
#define _BBS_CONFIG_H_

/*******************************************************************
 *    �����Өt�Ϊ��w�q
 *******************************************************************/
#define BBS_UID             9999        /* BBS user Run Time �t�� uid */
#define BBS_GID             999         /* BBS user Run Time �t�� gid */
#define MAXACTIVE           64         /* �u�W�e�\�H�� */
#define MAXBOARD            256
#ifndef HOMEBBS
/* a fallback in case we don't have the config.h */
#define HOMEBBS             "/home/bbs"
#endif

/*******************************************************************
 *    �t�βպA
 *******************************************************************/
#undef CHROOT_BBS                       /* �O�_�ϥ� chroot �H�W�[�t�Φw�� */
#define LOGINASNEW                      /* �O�_���\ new user */
#undef BBSLOG_MAIL                      /* �O�_�ҥι�~�e�H�O�� */
#undef BBSLOG_IDLEOUT                   /* �O�_�ҥ� IDLE �j���_�u�O�� */
#define BIT8                            /* �O�_�ϥΤ���� 8 bits �t��*/
#define INCLUDE_DEPTH       3           /* �t�A����, �O�d�X�h��� */
#define TREASURE_DEPTH      10          /* ��ذϳ̤j���h�`�� */
#define LEAST_IDLEN         (2)         /* userid �̵u���� */
#define GUEST               "guest"     /* �O�_�������[�αb���i�� */
#define LOCAL_MAX_MSQ       (8)         /* �^�U�T���ӼƤW�� */
#define MYCHARSET	    "big5"

/*******************************************************************
 *    ����{��
 *******************************************************************/
#define USE_IDENT                       /* �O�_�ϥλ{�Ҩt�� */
#define EMAIL_LIMIT 1                   /* �O�_����{�ҨϥΪ̱H���~�H */
#define PAGE_LIMIT  0                   /* �O�_����{�ҨϥΪ̲��/�e�T���\�� */
#define SYSOP_BIN                       /* �O�_�u�W�d�\�{�Ҹ�� */
#define USE_OVERRIDE_IN_LIST


/**************************************************************************
 *    ����@�ǥ\��ϥΪ��w�q
 **************************************************************************/
#define USE_VOTE                        /* �O�_�ϥΧ벼�t�� */
#define USE_MENUSHOW                    /* �O�_�ϥΨq�Ϭɭ� */
#undef USE_MULTI_LANGUAGE               /* �O�_�ϥΦh��y�� */
#if 0
#define USE_THREADING					/* syhu: threading on/off */
#define THREADUNIT_SIZE		10			/* syhu:.THREADPOST �ɴX�����@��� */
#endif

/*************************************************************************
 *   �H�U�u�A�Ω� NSYSU     BBS (���s�j�� BBS)
 *************************************************************************/
#if defined(ULTRABBS)|| defined(NSYSUBBS3) || defined(NSYSUBBS2) || defined(NSYSUBBS1) || defined(ANIMEBBS)
#define NSYSUBBS
#endif

#ifdef NSYSUBBS
# undef HOMEBBS
# define HOMEBBS "/apps/bbs"
# define ACTFILE     "conf/actfile"
# define CHROOT_BBS
# undef SYSOP_BIN
# undef LOCAL_MAX_MSQ
# define LOCAL_MAX_MSQ 20
/* kmwang: ���}�i mail Ū�H�ɷ� user ���\�� */
# define MAILWARN
/* kmwang: �}�� delete user ���\�� �b ULTRA ���ձN�H��H�� user ���\��*/
 #ifdef ULTRABBS
 # undef USE_DELUSER
/* kmwang: �䴩 YSNP server */
 # define NP_SERVER
 # define USE_ALOHA
 # undef MAXACTIVE
 # define MAXACTIVE (256)
 #endif
#endif

#if defined(PHBBS)
# undef HOMEBBS
# define HOMEBBS "/apps/bbs"
# undef MAXACTIVE
# define MAXACTIVE 100
/*
# define BBSNAME     "phbbs"
# define BBSTITLE    "��򿤱Ш|��������"
*/
#elif   defined(SSBBS)
# undef HOMEBBS
# define HOMEBBS "/apps/bbs"
# undef MAXACTIVE
# define MAXACTIVE 512
#elif   defined(KHBBS)
# undef HOMEBBS
# define HOMEBBS "/apps/bbs"
/*
# define BBSNAME     "khbbs"
# define BBSTITLE    "��������T�Ш|���� BBS ��"
*/
# define ACTFILE     "conf/actfile"
# define CHROOT_BBS
# undef MAXBOARD
# define MAXBOARD 384
# undef MAXACTIVE
# define MAXACTIVE 512
# define WEB_BOARD
# define CAPTURE_BOARD	"keepmessage"
/* ���� ID ���j�p�g */
//# define IGNORE_CASE
#elif   defined(STITBBS)
/*
# define BBSNAME     "shutebbs"
# define BBSTITLE    "��w�޳N�ǰ| BBS ��"
*/
# define ACTFILE     "conf/actfile"
# define CHROOT_BBS
#elif   defined(KGHSBBS)
# undef HOMEBBS
# define HOMEBBS "/apps/bbs"
/*
# define BBSNAME     "kghsbbs"
# define BBSTITLE    "�����k�� BBS ��"
# define MENU_TITLE_COLOR1      "[1;37;45m"
# define MENU_TITLE_COLOR     "[1;33;45m"
*/
# undef MAXACTIVE
# define MAXACTIVE (256)
# define ACTFILE     "conf/actfile"
# define CHROOT_BBS
/*
#elif	defined(ULTRABBS)
# define BBSNAME     "ultrabbs"
# define BBSTITLE    "���s�j�� Ultra BBS"
  */
# undef PAGE_LIMIT
# define PAGE_LIMIT 0
# define WEB_BOARD
#elif   defined(NSYSUBBS3)
/*
# define BBSNAME     "westbbs"
# define BBSTITLE    "���s�j�� West BBS-��l�W��"
# define HAVE_HOSTLIST
*/
# define NP_SERVER
# define USE_ALOHA
# undef PAGE_LIMIT
# define PAGE_LIMIT 0
# undef MAXACTIVE
# define MAXACTIVE (2048)
# undef MAXBOARD
# define MAXBOARD 4096
/*
#elif defined(NSYSUBBS2)
# define BBSNAME     "southbbs"
# define BBSTITLE    "���s�j�� South BBS-�n����"
# define MENU_TITLE_COLOR1      "[1;37;43m"
# define MENU_TITLE_COLOR     "[1;33;47m"
# undef MAXACTIVE
# define MAXACTIVE (600)
*/
#elif defined(ANIMEBBS)
# undef MAXACTIVE
# define MAXACTIVE (100)
/*
# define BBSNAME     "irradiance"
# define BBSTITLE    "�����j�� �� ����^��"
# define MENU_TITLE_COLOR1      "[1;33;42m"
# define MENU_TITLE_COLOR     "[0;37;42m"
*/
#elif defined(NSYSUBBS1)
/*
# define BBSNAME     "formosabbs"
# define BBSTITLE    "���s�j�� Formosa BBS-���R���q"
  */
# undef MAXACTIVE
# define MAXACTIVE (4096)
# undef MAXBOARD
# define MAXBOARD (4096)
# undef PAGE_LIMIT
# define PAGE_LIMIT 1
# define CAPTURE_BOARD	"keepmessage"
# define WEB_BOARD
# define STRICT_IDENT
# undef USE_OVERRIDE_IN_LIST
/*# define USE_ALOHA*/
#endif


#endif /* _BBS_CONFIG_H_ */
