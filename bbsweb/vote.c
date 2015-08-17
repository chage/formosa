
#include "bbs.h"


int
ShowVoteList(char *tag, char *POST_NAME)
{
	char *p, *para = NULL;
	char rtime[40], stime[40], etime[40];
	int num = 1;
	int fd;
	FILE *fp_out = stdout;
	VOTE ent;

	if ((p = strchr(tag, ' ')) != NULL)
	{
		*p = '\0';
		para = p + 1;
	}

#if 0
	fprintf(fp_out, "<%d>, tag=[%s], \n", request_rec->URLParaType, tag);
	fflush(fp_out);
#endif

	if ((fd = open(POST_NAME, O_RDONLY)) == 0)
		return FALSE;

	fprintf(fp_out, "[7m  %4s %-14.14s %12s %15s %4s %6s %6s %8s [m",
		       "�s��", "�벼�W��", "�|��H", "�W���ӷ�", "����",
		       "�W����", "�i�K��", "���U�ɶ�");
	fprintf(fp_out, "[7m  %4s %8s   %8s %8s[m",
		       "�{��", "�벼�}�l", "�w�p�}��", "�C�H����");

	while (read(fd, &ent, sizeof(VOTE)) == sizeof(VOTE))
	{
		if (ent.firstlogin)
			strftime(rtime, 11, "%Y.%m.%d", localtime(&(ent.firstlogin)));
		else
			strcpy(rtime, "����");

		fprintf(fp_out, "   %3d %-14.14s %12s %15s %4d %6d %6d %8s\n",
	       num, ent.title, ent.owner,
	       *(ent.allow_ip) ? ent.allow_ip : "����",
	       ent.userlevel, ent.numlogins, ent.numposts,
	       rtime);

		strftime(stime, 11, "%Y.%m.%d", localtime(&(ent.start_time)));
		strftime(etime, 11, "%Y.%m.%d", localtime(&(ent.end_time)));

		fprintf(fp_out, " %s %s - %s   %2d\n",
			       (ent.ident == 7) ? "��" : "  ",
			       stime, etime, ent.tickets);
		num++;
	}
	close(fd);

	return TRUE;
}


int
main()
{
	ShowVoteList("test", "/apps/bbs/boards/test/vote/.VOTE");
}
