
#include "bbs.h"
#include "tsbbs.h"


extern struct commands MainMenu[];


/*******************************************************************
 * Admin Menu
 *******************************************************************/

struct commands AdminMenu[] =
{
	{'i', PERM_SYSOP, NULL, adminMaintainUser, ADMIN, "User Info", "���ϥΪ̸��"},
	{'l', PERM_SYSOP, NULL, adminDisplayUserLog, ADMIN, "User Log", "��ܨϥΪ̰O��"},
#ifdef USE_DELUSER
	{'d', PERM_SYSOP, NULL, adminDeleteUser, ADMIN, "Delete User", "�R���@��ϥΪ�"},
#endif
	{'n', PERM_SYSOP, NULL, adminCreateBoard, ADMIN, "New Board", "�إ߷s�ݪO"},
	{'m', PERM_SYSOP, NULL, adminMaintainBoard, ADMIN, "Modify Board", "���/�R��/��z�ݪO�]�w"},
	{'e', PERM_SYSOP, NULL, adminEditConf, ADMIN, "Edit Config", "�s��]�w�ɮ�"},
	{'u', PERM_SYSOP, NULL, adminListUsers, LAUSERS, "List All Users", "�C�X�Ҧ��ϥΪ�"},
#if 0
	{'k', PERM_SYSOP, NULL, adminKickUser, ADMIN, "Kick User", "�N�u�W�ϥΪ��_�u"},
#endif
	{'a', PERM_SYSOP, NULL, adminBroadcast, SENDMSG, "BroadCast", "�����s��"},
	{'b', PERM_SYSOP, NULL, adminMailBm, SMAIL, "Mail to all BMs", "�H�H���Ҧ��O�D"},
#if defined(NSYSUBBS1) || defined(NSYSUBBS3) /* sarek:03/30/2001 */
/* TODO */
	{'c', PERM_SYSOP, NULL, adminCancelUser, ADMIN, "Cancel User", "���ΨϥΪ̱b��"},
#endif
#ifndef NSYSUBBS
	{'s', PERM_SYSOP, NULL, adminSyscheck, ADMIN, "Manually Check Ident", "��ʨ����{��"},
#endif
#ifdef ANIMEBBS
	{'a', PERM_SYSOP, MainMenu, NULL, ADMIN, "Admin Menu", "���x�K��"},
#else
	{'a', PERM_SYSOP, MainMenu, NULL, ADMIN, "Admin Menu", "�޲z�̿줽��"},
#endif
	{0, PERM_SYSOP, NULL, NULL, 0, NULL, NULL}
};


/*******************************************************************
 * Xyz Menu
 *******************************************************************/

struct commands XyzMenu[] =
{
	{'d', 1, NULL, x_info, 0, "Personal Data", "��ܻP�ק�ӤH�򥻸��"},
	{'u', 0, NULL, x_uflag, 0, "User Option", "�����ӤH�ϥγ]�w"},
	{'o', 1, NULL, x_override, OVERRIDE, "Override Edit", "�s��n�B�ͦW��"},
	{'l', 1, NULL, x_blacklist, BLACKLIST, "Blacklist Edit", "�s���a�H�W��"},
	{'s', 1, NULL, x_signature, EDITSIG, "Signature Edit", "�s��ñ�W��"},
	{'n', 1, NULL, x_plan, EDITPLAN, "Plan Edit", "�s��W����"},
	{'t', 0, NULL, x_date, 0, "Time Now", "��ܲ{�b�t�ήɶ�"},
	{'v', 0, NULL, x_viewnote, 0, "View Note", "�d�\\�d��"},
	{'b', 0, NULL, x_bakpro, 0, "Backup Personal Data", "�ƥ��p�H���"},
#ifdef USE_IDENT
	{'c', 1, NULL, x_idcheck, 0, "ID Check", "�i�樭���T�{"},
#endif
	{'x', 0, MainMenu, NULL, XMENU, "Xyz Menu", "�ӤH��ƺ��@�u��c"},
	{0, 0, NULL, NULL, 0, NULL, NULL}
};


/*******************************************************************
 * Mail Menu
 *******************************************************************/

struct commands MailMenu[] =
{
	{'n', 1, NULL, m_new, RMAIL, "New Mails", "�uŪ�s���H"},
	{'r', 1, NULL, m_read, RMAIL, "Read Mails", "�˵��Ҧ��H��"},
	{'s', 1, NULL, m_send, SMAIL, "Send Mail", "�H�H"},
	{'g', 1, NULL, m_group, SMAIL, "Mail to Group", "�H�H���h�H"},
#ifdef ANIMEBBS
	{'m', 0, MainMenu, NULL, MAIL, "Mail Menu", "��������F"},
#else
	{'m', 0, MainMenu, NULL, MAIL, "Mail Menu", "�ӤH�H�c"},
#endif
	{0, 0, NULL, NULL, 0, NULL, NULL}
};


/*******************************************************************
 * Talk Menu
 *******************************************************************/

struct commands TalkMenu[] =
{
	{'u', 0, NULL, t_list, LUSERS, "Online Users", "���C�X���b�u�W���ϥΪ�"},
	{'f', 1, NULL, t_friends, LFRIENDS, "Friends Online", "�C�X���b�u�W���ѪB��"},
	{'q', 0, NULL, t_query, QUERY, "Query User", "�d�ߨϥΪ̭ӤH��ƲӶ�"},
	{'p', 1, NULL, t_pager, PAGE, "Pager Switch", "������ѩI��a"},
	{'d', 1, NULL, t_bpager, PAGE, "Broadcast Pager Switch", "�����s���I��a"},
	{'t', 1, NULL, t_talk, PAGE, "Talk", "���H�ͤ߶���"},
	{'c', 3, NULL, t_chat, CHATROOM, "BBS Chat Room", "������Ѽs��"},
	{'b', 1, NULL, t_fmsq, SENDMSG, "BroadCast", "�e�T�����n��"},
	{'w', 1, NULL, t_msq, SENDMSG, "Send Message", "�u�W�e�T��"},
	{'r', 1, NULL, t_review, SENDMSG, "Review Message", "�^�U�u�W�T��"},
	{'t', 0, MainMenu, NULL, TMENU, "Talk Menu", "�𶢲�Ѷ�a"},
	{0, 0, NULL, NULL, 0, NULL, NULL}
};


/*******************************************************************
 * Main Menu
 *******************************************************************/

#ifdef ANIMEBBS
struct commands MainMenu[] =
{
	{'c', 0, NULL, Class, CLASS_MENU, "Class", "����^�����Ϲ�"},
	{'n', 0, NULL, Announce, READING, "Announce", "�����o���H"},
	{'0', 0, NULL, Boards, BOARDS_MENU, "Boards", "����^��������"},
	{'s', 0, NULL, Select, SELECT, "Select", "����^�����N��"},
	{'r', 0, NULL, MainRead, READING, "Read", "Ū���G�i"},
	{'t', 0, &(TalkMenu[0]), NULL, TMENU, "Talk Menu", "���t�d���۳{�U"},
	{'m', 1, &(MailMenu[0]), NULL, MAIL, "Mail Menu", "��������F"},
	{'x', 0, &(XyzMenu[0]), NULL, XMENU, "Xyz Utilities", "�u���"},
#ifdef USE_MULTI_LANGUAGE
	{'l', 0, NULL, x_lang, 0, "Language switch", "�����y������"},
#endif
	{'g', 0, NULL, Goodbye, 0, "Goodbye", "�p�O����^��"},
	{'a', PERM_SYSOP, &(AdminMenu[0]), NULL, ADMIN, "Admin Menu", "���x�K��"},
	{'0', 0, NULL, NULL, MMENU, "Main Menu", "�D���"},
	{0, 0, NULL, NULL, 0, NULL, NULL}
};
#else
struct commands MainMenu[] =
{
	{'c', 0, NULL, Class, CLASS_MENU, "Class", "�������G�i����"},
	{'n', 0, NULL, Announce, READING, "Announce", "�i�����i"},
	{'0', 0, NULL, Boards, BOARDS_MENU, "Boards", "��Ц��G�i����"},
	{'s', 0, NULL, Select, SELECT, "Select", "��J���G�i����"},
	{'r', 0, NULL, MainRead, READING, "Read", "Ū���G�i"},
	{'t', 0, &(TalkMenu[0]), NULL, TMENU, "Talk Menu", "�𶢲�Ѷ�a"},
	{'m', 1, &(MailMenu[0]), NULL, MAIL, "Mail Menu", "�ӤH�l��H�c"},
	{'x', 0, &(XyzMenu[0]), NULL, XMENU, "Xyz Utilities", "�ӤH��ƺ��@�u��c"},
#ifdef USE_MULTI_LANGUAGE
	{'l', 0, NULL, x_lang, 0, "Language switch", "�����y������"},
#endif
	{'g', 0, NULL, Goodbye, 0, "Goodbye", "�A���A�ڪ��B��"},
	{'a', PERM_SYSOP, &(AdminMenu[0]), NULL, ADMIN, "Admin Menu", "�޲z�̿줽��"},
	{'0', 0, NULL, NULL, MMENU, "Main Menu", "�D���"},
	{0, 0, NULL, NULL, 0, NULL, NULL}
};
#endif


/*******************************************************************
 * Menu Operation
 *******************************************************************/

int menu_depth = 1;
static int n_cmenus = 0;
struct commands *cmenus = MainMenu;
short redraw;

#ifdef USE_MENUSHOW
int pict_no = 0;
struct MenuShowShm *msshm;
#endif

static void menu_title()
{
	title_func(cmenus[n_cmenus - 1].chelp, BBSTITLE);

#ifdef USE_MENUSHOW
	if (redraw && !(curuser.flags[0] & PICTURE_FLAG))
	{
		if (msshm == NULL)
			msshm = (struct MenuShowShm *) attach_shm(MENUSHOW_KEY, sizeof(struct MenuShowShm));
		if (msshm && msshm->number)
		{
			int j;
			char *p1, *p2;
			unsigned char chs;
			static long randomseed = 1;

			/*
			 * This is a simple linear congruential random number
			 * generator.  Hence, it is a bad random number
			 * generator, but good enough for most randomized
			 * geometric algorithms. modify by lthuang
			 */
			randomseed = (randomseed * 1366l + 150889l) % 714025l;
			pict_no = randomseed / (714025l / msshm->number + 1);

/*
 * j = n_cmenus + 2;
 * if (j < 13)
 * j = 13;
 */
			move(10, 0);
			outs(ANSI_COLOR(1;32) "(TAB) �i�}����" ANSI_RESET);
			move(10, 69 - strlen(msshm->list[pict_no].owner));
			prints("�i���ѡj%s ", msshm->list[pict_no].owner);
			j = 2;
			move(j, 0);
/*
 * prints("[7m�m�@�̡n%35.35s  �m���D�n%27.27s[m",
 * msshm->list[pict_no].owner, msshm->list[pict_no].title);
 */
			p1 = msshm->list[pict_no].body;

/*
 * while (j++ < b_line)
 */
			while (++j < 11)
			{
				if ((p2 = strchr(p1, '\n')) != NULL)
					p1 = ++p2;
				else
					break;
			}
			/*
			 * Direct output the content in shared memory,
			 * for better performance. by lthuang
			 */
			j = p1 - msshm->list[pict_no].body;
			p1 = msshm->list[pict_no].body;
			while (j-- > 0 && (chs = *p1++) != '\0')
				outc(chs);
			outs(ANSI_RESET);

			redraw = FALSE;
		}
/*
 * move(b_line, 0);
 */
	}
#endif /* USE_MENUSHOW */
}


static void menu_btitle()
{
	prints(_msg_menu_2, pagerstring(&uinfo));
}


static void menu_entry(int x, void *ep, int idx, int top, int last, int rows)
{
	struct commands *ent = (struct commands *)ep;
	int i, num;

	for (num = top; num <= last; num++)
	{
		i = num - top;
		if (i >= rows)
			break;

		i = x;
		while (i-- > 0)
			outc(' ');

		i = num - idx;
		prints("   ([1;3%cm%c[m) %-23s %s\n",
		       (menu_depth == 1) ? '2' : '6',
		       ent[i].key, ent[i].ehelp, ent[i].chelp);
	}
}

static int is_sysop_host(const char *from)
{
	char *p = SYSOP_HOSTS, *ep;

	if (!strcmp(SYSOP_HOSTS, "ALL"))
		return 1;

	while ((ep = strchr(p, ',')) != NULL) {
		if (!strncmp(from, p, ep - p))
			return 1;
		p = ep + 1;
	}
	if (strlen(p))
		return !strncmp(from, p, strlen(p));
	return 0;
}

static int menu_max(char *direct, int size)
{
	int i, j;

	for (i = 0, j = 0; cmenus[i].key; i++)
	{
#ifdef USE_IDENT
		if (cmenus[i].cfunc == x_idcheck && curuser.ident == 7)
			continue;
#endif
		if (curuser.userlevel < cmenus[i].level)
			continue;
		if (cmenus[i].level == PERM_SYSOP)
		{
#ifdef NSYSUBBS
			extern BOOL IsRealSysop;

			if (!IsRealSysop)
				continue;
#endif
			if (!is_sysop_host(uinfo.from))
				continue;
		}
		if (j != i)
			memcpy(&(cmenus[j]), &(cmenus[i]), sizeof(struct commands));
		j++;
	}
	if (j != i)
		memcpy(&(cmenus[j]), &(cmenus[i]), sizeof(struct commands));
	update_umode(cmenus[j - 1].mode);

#if 0
	if (uinfo.mode == ADMIN && !HAS_PERM(PERM_SYSOP))	/* debug */
	{
		bbsd_log_write("ERR", "not sysop, but enter (A)dmin");
		exit(0);
	}
#endif

	n_cmenus = j;
	return j - 1;
}


static int menu_get(char *direct, void *s, int size, int top)
{
	int n = n_cmenus - top /*+ 1*/;
	extern int autoch;

	/* if new mail available, key move to the function automatically */
	if (menu_depth == 1 && CheckNewmail(curuser.userid, FALSE))
		autoch = 'm';

	if (n > ROWSIZE)
		n = ROWSIZE;
	memcpy(s, cmenus, n * size);
	return n;
}


static int menu_findkey(char *nbuf, void *ep, register int start, register int total)
{
	/* by Keeper:
	   start and total are not in the list,
	   so I guess they are register int.
	   Maybe they are int?
	   By CD:
	   It doesn't matter actually. :p
	   */
	struct commands *ent = (struct commands *)ep;
	register int i;

	for (i = start; i < total; i++)
	{
		if (ent[i].key == *nbuf)
		{
			nbuf[0] = '\0';
			return (i + 1);
		}
	}
	for (i = 0; i < start; i++)
	{
		if (ent[i].key == *nbuf)
		{
			nbuf[0] = '\0';
			return (i + 1);
		}
	}
	nbuf[0] = '\0';
	return -1;
}


static int mcmd_menushow(int ent, struct commands *cent, char *direct)
{
	if (!(curuser.flags[0] & PICTURE_FLAG))
	{
		pmore(msshm->list[pict_no].filename, TRUE);
		redraw = TRUE;
		return C_FULL;
	}
	return C_NONE;
}


static int mcmd_enter(int ent, struct commands *cent, char *direct)
{
	if (cent->comm)
	{
		cmenus = cent->comm;	/* �i�J�l��� */
		menu_depth++;
		return C_REDO;
	}
	update_umode(cent->mode);
	redraw = TRUE;
	return (*(cent->cfunc)) ();
}



struct one_key menu_comms[] =
{
	{'\t', mcmd_menushow},
	{'r', mcmd_enter},
	{0, NULL}
};


void domenu()
{
	int m_ccur[4];

#ifdef USE_VOTE
	CheckNewSysVote();
#endif

	memset(m_ccur, 0, sizeof(m_ccur));

	for (;;)
	{
		redraw = TRUE;

		if (cursor_menu(11, 13, NULL, menu_comms, sizeof(struct commands),
				&(m_ccur[menu_depth - 1]),
				menu_title, menu_btitle, menu_entry, menu_get, menu_max,
				menu_findkey, 0, TRUE) == 0)
		{
			if (menu_depth == 1)
			{
				Goodbye();
			}
			else
			{
				menu_depth--;	/* �h�^�W�h��� */
				m_ccur[menu_depth] = 0;
				cmenus = cmenus[n_cmenus - 1].comm;
			}
		}
	}
}
