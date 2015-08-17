
/* ##### CAUTION: THIS VERSION IS MODIFIED FOR CURRENT LEVEL SETTING ##### */
/*
   RULES:
	�b���۰ʲM����h
	1.����0-30 �šG�O�d30��  (30�ѥ��W�u�̧Y�M��)
	  ����31-49�šG�O�d60��  (60�ѥ��W�u�̧Y�M��)
	  ����50   �šG�O�d90��  (90�ѥ��W�u�̧Y�M��)
	  ����100  �šG�O�d365�� (365�ѥ��W�u�̧Y�M��)
	  ����255  �šG�����n�H�W�̡A�ä��M��
	2.�L�׬O�_�q�L�{�ҡA�Ҥ�ӿ�z
	3.�Y��_�����H�����O�d�b�����S�ҡA
	  ��Y�H�������ӱ`�۰ʲM���b��

	by sarek < sarek@cc.nsysu.edu.tw > , 05/13/2002 */

#include "bbs.h"
#include <sys/stat.h>


#undef DEBUG


#define DEL_USER3	(10)	/* �� */
#define DEL_USER0	(30)	/* �� */
#define DEL_USER50	(90)	/* �� */
#define DEL_USER100	(365)	/* �� */

#define DEL_HOME	"home/.del"
#define DEL_MAIL	"mail/.del"
#define RPT_BOARD	"user-stat"

#define RPT_DELUSER	"log/rpt.deluser"
#define RPT_BM		"log/rpt.bm"
#define RPT_SYSOP	"log/rpt.sysop"
#define RPT_TOTAL	"log/rpt.total"

#define IMPOSSIBLE_TIME (400*24*60*60)

time_t  now, duser0, duser31, duser50, duser100;
/* sarek:05/13/2002:�����@�U,�o�O�ڷs�t��,���Ӫ��Oduser0��duser3�ۤ� -_-
	duser0�O��0-30��
	duser31�O��31-49��
	duser50�O��50��
	duser100�O��100��
*/
int     total_user, total_bm, total_sysop, total_del, total_ident;


int
CheckDir()
{
	struct stat st;

	if (stat(DEL_HOME, &st))
	{
		if (mkdir(DEL_HOME, 0700))
			return -1;
	}
	else if (!S_ISDIR(st.st_mode))
		return -1;

	if (stat(DEL_MAIL, &st))
	{
		if (mkdir(DEL_MAIL, 0700))
			return -1;
	}
	else if (!S_ISDIR(st.st_mode))
		return -1;

	return 0;
}



/*
The accounts not expired never
	m??????????
	me??????????
	d??????????
--lasehu
*/
int
IsExpire(u)
USEREC *u;
{
	if (u->lastlogin > duser0)
		return 0;
	else if (u->userlevel == 255)
		return 0;
	else if (!strcmp(u->userid, "SYSOP")
#ifdef GUEST
		 || !strcmp(u->userid, GUEST)
#endif
		)		/* lasehu */
	{
		return 0;
	}
/*
	else if (u->lastlogin <= 0 || (u->lastlogin < (now - IMPOSSIBLE_TIME)))
		return 0;
*/
#if 1
/* lasehu */
	if (u->lastlogin <= 0 || (u->lastlogin < (now - IMPOSSIBLE_TIME)))
	{
		char buf[PATHLEN];
		struct stat st;

		sethomefile(buf, u->userid, UFNAME_PASSWDS);
		if (stat(buf, &st) == 0 && st.st_mtime > 0)
			u->lastlogin = st.st_mtime;
	}
#endif
	if (u->userlevel >= 100)
	{
		if (u->lastlogin < duser100)
			return 1;
	}
	else if (u->userlevel >= 50)
	{
		if (u->lastlogin < duser50)
			return 1;
	}
	else if (u->userlevel >= 31)	/* sarek:05/13/2002: ���ӬO <= ...�ڷQ�i��Oduser0��duser3�d���F -_- */
	{
		if (u->lastlogin < duser31)
			return 1;
	}
	else
	{
		if (u->lastlogin < duser0)
			return 1;
	}
	return 0;
}



int
DelUser()
{
	char    aha[] = "0abcdefghijklmnopqrstuvwxyz";
	DIR    *dirp;
	struct dirent *dent;
	char    id[IDLEN + 2];
	char    path[512], path2[512];
	char    upath[80], ppath[80];
	int     i, fd, fdi, fdp, expire;
	FILE   *fpr, *fpbm, *fpsys, *fpt;
	USEREC user;

	for (i = 0; i < 27; i++)
	{
		sprintf(path, "%s/%c", DEL_HOME, aha[i]);
		mkdir(path, 0700);
		chown(path, BBS_UID, BBS_GID);
		sprintf(path, "%s/%c", DEL_MAIL, aha[i]);
		mkdir(path, 0700);
		chown(path, BBS_UID, BBS_GID);
	}

	sprintf(upath, "%s.new", USERIDX);
	sprintf(ppath, "%s.new", PASSFILE);
	if ((fdi = open(upath, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		return -1;
	if ((fdp = open(ppath, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
	{
		close(fdi);
		return -1;
	}
	if ((fpr = fopen(RPT_DELUSER, "w")) == NULL)
	{
		fprintf(stderr, "cannot create: %s\n", RPT_DELUSER);
		exit(1);
	}
	if ((fpbm = fopen(RPT_BM, "w")) == NULL)
	{
		fprintf(stderr, "cannot create: %s\n", RPT_BM);
		exit(1);
	}
	if ((fpsys = fopen(RPT_SYSOP, "w")) == NULL)
	{
		fprintf(stderr, "cannot create: %s\n", RPT_SYSOP);
		exit(1);
	}

	fprintf(fpr, "         Current Date: %s", ctime(&now));
	fprintf(fpr, " Lv. 0-30 Expire Date: %s", ctime(&duser0));
	fprintf(fpr, "Lv. 31-49 Expire Date: %s", ctime(&duser31));
	fprintf(fpr, "   Lv. 50 Expire Date: %s", ctime(&duser50));
	fprintf(fpr, "  Lv. 100 Expire Date: %s", ctime(&duser100));
	fprintf(fpr, "%s", "==============================================\n");
	fprintf(fpbm, "Date: %s", ctime(&now));
	fprintf(fpsys, "Date: %s", ctime(&now));
	for (i = 0; i < 27; i++)
	{
		sprintf(path, "home/%c", aha[i]);
		if (!(dirp = opendir(path)))
			continue;
		readdir(dirp);	/* skip . & .. */
		readdir(dirp);
		while ((dent = readdir(dirp)) != NULL)
		{
			if (dent->d_name[0] == '\0')
				continue;

			expire = 0;
			memset(id, '\0', sizeof(id));
			strncpy(id, dent->d_name, sizeof(id) - 1);
			sprintf(path, "home/%c/%s/passwds", aha[i], id);
			if ((fd = open(path, O_RDONLY)) < 0)
			{
				fprintf(fpr, "Error:[%s] no file\n", id);
				expire = 2;
			}
			else
			{
				if (read(fd, &user, sizeof(user)) != sizeof(user))
				{
					fprintf(fpr, "Error:[%s] size err\n", id);
					expire = 3;
				}
				else
				{
					if ((expire = IsExpire(&user)) == 0)
					{
						total_user++;
						if (user.ident == 7)
							total_ident++;
					}
				}
				close(fd);
			}
			if (expire)
			{
				sprintf(path, "home/%c/%s", aha[i], id);
				sprintf(path2, "%s/%c/%s", DEL_HOME, aha[i], id);
#ifndef DEBUG
				if (rename(path, path2))
					fprintf(fpr, "Error:[%s] rename\n", id);
				else
#endif
				{
					sprintf(path, "mail/%c/%s", aha[i], id);
					sprintf(path2, "%s/%c/%s", DEL_MAIL, aha[i], id);
#ifndef DEBUG
					myrename(path, path2);
#endif
					if (expire == 1)
					{
						static char tibuf[20];

						strftime(tibuf, sizeof(tibuf), "%m/%d/%Y %X",
						 	localtime(&(user.lastlogin)));
						fprintf(fpr, "[%12s] level:[%3d] %s\n", id,
							user.userlevel, tibuf);
/*
   fprintf(fpr, "[%12s] level:[%3d]  %s", id,
   user.userlevel, ctime(&(user.lastlogin)));
 */
					}
					else
						fprintf(fpr, "[%s] clean err.%d\n", id, expire);
					total_del++;
					continue;
				}
			}
			if (user.userlevel >= 255)
			{
				total_sysop++;
				fprintf(fpsys, "%12s %d\n", id, user.userlevel);
			}
			else if (user.userlevel >= 100)
			{
				total_bm++;
				fprintf(fpbm, "%12s %d\n", id, user.userlevel);
			}
			write(fdi, user.userid, sizeof(user.userid));
			write(fdp, &user, sizeof(user));
		}
		closedir(dirp);
	}
	close(fdi);
	close(fdp);

	if ((fpt = fopen(RPT_TOTAL, "w")) != NULL)
	{
		fprintf(fpt, "\n########## �����ϥΪ� ##########\n");
		fprintf(fpt, "# �R���H��: %d\n", total_del);
		fprintf(fpt, "# �{�b�H��: %d\n", total_user);
		fprintf(fpt, "# �{�ҤH��: %d\n", total_ident);
		fprintf(fpt, "# ���D�H��: %d\n", total_bm);
		fprintf(fpt, "# �����H��: %d\n", total_sysop);
		fclose(fpt);
	}

	fclose(fpr);
	fclose(fpbm);
	fclose(fpsys);
	chown(upath, BBS_UID, BBS_GID);
	chown(ppath, BBS_UID, BBS_GID);
	unlink(USERIDX);
	rename(upath, USERIDX);
	unlink(PASSFILE);
	rename(ppath, PASSFILE);
	return 0;
}


int
PostRpt()
{
	char    today[40], buf[4096], fname[PATHLEN], title[STRLEN];
	int     fdr, cc, retval;
	FILE   *fpw;

	sprintf(today, "%s", ctime(&now));
	today[strlen(today) - 1] = '\0';
	sprintf(title, "�ϥΪ̧R�����i  %s", today);

	sprintf(fname, "tmp/.deluser_post");
	if ((fpw = fopen(fname, "w")) < 0)
		return -1;

	chown(fname, BBS_UID, BBS_GID);

	write_article_header(fpw, "SYSOP", "�t�κ޲z��", RPT_BOARD, today,
			     title, NULL);
	fprintf(fpw, "\n");

	if ((fdr = open(RPT_TOTAL, O_RDONLY)) > 0)
	{
		while ((cc = read(fdr, buf, sizeof(buf))) > 0)
			fwrite(buf, cc, 1, fpw);
		close(fdr);
	}

	if ((fdr = open(RPT_DELUSER, O_RDONLY)) > 0)
	{
		while ((cc = read(fdr, buf, sizeof(buf))) > 0)
			fwrite(buf, cc, 1, fpw);
		close(fdr);
	}

	fprintf(fpw, "\n########## ���D���i ##########\n");
	if ((fdr = open(RPT_BM, O_RDONLY)) > 0)
	{
		while ((cc = read(fdr, buf, sizeof(buf))) > 0)
			fwrite(buf, cc, 1, fpw);
		close(fdr);
	}

	fprintf(fpw, "\n########## �������i ##########\n");
	if ((fdr = open(RPT_SYSOP, O_RDONLY)) > 0)
	{
		while ((cc = read(fdr, buf, sizeof(buf))) > 0)
			fwrite(buf, cc, 1, fpw);
		close(fdr);
	}

	fclose(fpw);

#ifdef USE_THREADING	/* syhu */
	retval = PublishPost(fname, "SYSOP", "�t�κ޲z��", RPT_BOARD, title, 7,
			             "localhost", FALSE, NULL, 0, -1, -1);
#else
	retval = PublishPost(fname, "SYSOP", "�t�κ޲z��", RPT_BOARD, title, 7,
			             "localhost", FALSE, NULL, 0);
#endif
	unlink(fname);
	return retval;
}


int
main(argc, argv)
int     argc;
char   *argv[];
{
	if (argc < 5)	/* sarek:05/13/2002:��[BBSHomeDir]����,�w���ϥΤF... */
	{
		printf("Usage: %s [��(30�ťH�U)] [��(50�ťH�U)] [��(50��)] [��(100��)]\n", argv[0]);
		printf("Default: %s 30 60 90 365\n", argv[0]);
		exit(0);
	}

	init_bbsenv();

/*
	duser3 = DEL_USER3;
	duser0 = DEL_USER0;
	duser50 = DEL_USER50;
	duser100 = DEL_USER100;
*/
	duser0 = atoi(argv[1]);		/* sarek:05/13/2002: duser0�O��0�Ũ�31�Ť����� */
	duser31 = atoi(argv[2]);	/* sarek:05/13/2002: ���ӬOargv[1],�ڷQ�O���e�˿��F�a... */
	duser50 = atoi(argv[3]);
	duser100 = atoi(argv[4]);

	now = time(0);
	if ((duser0 = now - (duser0 * 24 * 60 * 60)) <= 0)
		exit(-1);
	if ((duser31 = now - (duser31 * 24 * 60 * 60)) <= 0)
		exit(-1);
	if ((duser50 = now - (duser50 * 24 * 60 * 60)) <= 0)
		exit(-1);
	if ((duser100 = now - (duser100 * 24 * 60 * 60)) <= 0)
		exit(-1);
	if (CheckDir())
		exit(-1);

	total_user = total_bm = total_sysop = total_del = total_ident = 0;

	DelUser();
	PostRpt();

	return 0;
}

#if 0
/*******************************************************************
 * �R���@��ϥΪ̪����
 * �Ѽ�: name -> userid
 * �Ǧ^: �ϥΪ̽s��. if failed, return 0;
 *******************************************************************/
unsigned int
delete_user(name)
char   *name;
{
	int     fd;
	unsigned int uid;
	struct useridx uidx;

	if (name == NULL || name[0] == '\0')
		return 0;
	if ((uid = get_passwd(NULL, name)) <= 0)
		return 0;
	if ((fd = open(USERIDX, O_RDWR)) < 0)
		return 0;
	flock(fd, LOCK_EX);

	prints("\n�M��ϥΪ̯��ްO�� ... ");
	bbslog("DELUSER", "name:[%s] uid:[%d]", name, uid);

	if (lseek(fd, (uid - 1) * sizeof(uidx), SEEK_SET) != -1
	    && read(fd, &uidx, sizeof(uidx)) == sizeof(uidx)
	    && !strcmp(uidx.userid, name)
	    && lseek(fd, -((off_t) sizeof(uidx)), SEEK_CUR) != -1)
	{
		memset(&uidx, 0, sizeof(uidx));
		if (write(fd, &uidx, sizeof(uidx)) == sizeof(uidx))
		{
			flock(fd, LOCK_UN);
			close(fd);
#if 0
			log_usies("DELUSER", "delete [%s] user file", name);
#endif
			delete_user_file(name);
			return uid;
		}
	}
	flock(fd, LOCK_UN);
	close(fd);
	return 0;
}

#endif
