
#ifndef _BBS_MODES_H
#define _BBS_MODES_H

/* Lots o' modes! */	/* see mode in struct user_info in bbs.h */

enum modes {
	MMENU, /* "�D���" */
	XMENU, /* "�u����" */
/*
 GMENU, "�T�ֳ�"
 */
	ADMIN, /* "�޲z��" */
	BOARDS_MENU, /* "�ݪO���" */
	CLASS_MENU, /* "�������" */
	MAIL, /* "�H����" */
	READING, /* "Ū�G�i" */
	POSTING, /* "�K�G�i" */
	MODIFY, /* "�ק�峹" */
	RMAIL, /* "Ū�H" */
/*
 READNEW, "Ū�s�H"
 */
	SMAIL, /* "�H�H" */
	TMENU, /* "�͸ܿ��" */
	TALK, /* "���" */
	PAGE, /* "�I��a" */
	LUSERS, /* "�d�u�W�H" */
	LFRIENDS, /* "�ݦѪB��" */

	CHATROOM, /* "������ѫ�" */
	CHATROOM2, /* "���߯���" for nsysubbs */
#if 0
	IRCCHAT, /* "�ꤺ��Ѽs��" */
	LOCALIRC, /* "�󯸲�Ѽs��" */
#endif
	SENDMSG, /* "�u�W�e�T��" */
/*
	ULDL, "����"
*/
	QUERY, /* "�d�߬Y�H" */
	SELECT, /* "��ݪO" */
	EDITSIG, /* "�sñ�W��" */
	EDITPLAN, /* "�s�W����" */
	OVERRIDE, /* "�s�n�ͦW��" */
	BLACKLIST, /* "�s�a�ͦW��" */
	LOGIN, /* "ñ�줤" */

	LAUSERS, /* "�d�����H" */
/*
	MONITOR, "�ʬݤ�"
*/
	CLIENT, /* "�D�q���\\����" */
	WEBBBS, /* "Web-BBS" */
/*
   NEW, "�s�ϥΪ̵��U"
 */
	VOTING, /* "�벼��" */
	EDITBMWEL, /* "�s�i�O�e��" */
	UNDEFINE /* "���w�q" */
};


// values returned by pager
#define RET_DOREPLY	    (999)
#define RET_DORECOMMEND	    (998)
#define RET_DOQUERYINFO	    (997)
#define RET_DOSYSOPEDIT	    (996)
#define RET_DOCHESSREPLAY   (995)
#define RET_DOBBSLUA	    (994)
#define RET_COPY2TMP	    (993)
#define RET_SELECTBRD	    (992)
#define RET_DOREPLYALL	    (991)

/* common return values of article.c and pmore.c */
enum {
	DONOTHING,	/* Read menu command return states */
	FULLUPDATE,	/* Entire screen was destroyed in this oper */
	PARTUPDATE,	/* Only the top three lines were destroyed */
	DOQUIT,		/* Exit read menu was executed */
	NEWDIRECT,	/* Directory has changed, re-read files */
	READ_NEXT,	/* Direct read next file */
	READ_PREV,	/* Direct read prev file */
	DIRCHANGED,	/* Index file was changed */
	READ_REDRAW,
	PART_REDRAW,
	TITLE_REDRAW,
	READ_SKIP,
	HEADERS_RELOAD,

	RELATE_FIRST,
	RELATE_NEXT,
	RELATE_PREV,
	NEWPOST_NEXT,
	NEWPOST_PREV,
	AUTHOR_NEXT,
	AUTHOR_PREV

};
#endif	/*_BBS_MODES_H */
