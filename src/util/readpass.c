
/*
readpass                show userinfo only, need indicate path.
*/

#include "bbs.h"


int
main (argc, argv)
     int argc;
     char *argv[];
{
	int fd;
	char userid[IDLEN + 2], fn[STRLEN];
	USEREC curuser;

	if (argc < 3)
	{
		printf ("Usage:  %s  [userid] [filename]\n", argv[0]);
		exit (0);
	}

	strcpy (userid, argv[1]);
	strcpy (fn, argv[2]);

	if ((fd = open (fn, O_RDONLY)) < 0)
	{
		printf ("\nError: cannot open %s\n", fn);
		exit (0);
	}

	printf ("Searching %s's Data ...", userid);

	while (read (fd, &curuser, sizeof (curuser)) == sizeof (curuser))
	{
		if (!strcmp (curuser.userid, userid))
		{
			printf ("Found !");
			printf ("\n-----------------------------------------------------------\n");
			printf ("�� �N�W (userid) : %s\n", curuser.userid);
			printf ("�� �ʺ� (username) : %s\n", curuser.username);
			printf ("�� �T�{�{�� : %d\n", curuser.ident);
			printf ("�� �q�l�l�c : %s\n", curuser.email);
/*
   printf("�� �׺ݾ��� : %s\n", curuser.termtype);
 */
			printf ("�� �W���`�� : %d ��\n", curuser.numlogins);
			printf ("�� �i�K�`�� : %x �g\n", curuser.numposts);
			printf ("�� �ثe�ż� : %d\n", curuser.userlevel);
			printf ("�� ���U�s�� : %d\n", curuser.uid);
			printf ("�� �K�X : %s\n", curuser.passwd);
			printf ("�� �W���W�� : [%x] %s", curuser.lastlogin, ctime (&curuser.lastlogin));
			printf ("�� ���U�ɶ� : [%x] %s", curuser.firstlogin, ctime (&curuser.firstlogin));
			printf ("�� �۰���H : %s\n", (curuser.flags[0] & FORWARD_FLAG) ? "�Ұ�" : "����");
			printf ("�� �W���ϥ� : %s", (curuser.lastctype == CTYPE_CSBBS) ? "Client" : "Telnet");
			if (curuser.passwd[0] == '\0')
				printf ("\npasswd null\n");
			close (fd);
			return 1;
		}
	}
	printf ("Not Found !\n");
	close (fd);

	return 0;
}
