/* ------------------- */
/* arbeiter.h          */
/* (c) by marcel block */
/* --------------------*/

#ifndef _ARBEITER_H_
#define _ARBEITER_H_

#define ARBEITER_MOC		0
#define ARBEITER_KOMPILIEREN		1
#define ARBEITER_ALLE_KOMPILIEREN	2
#define ARBEITER_LINKEN				3
#define ARBEITER_RUNDSCHLAG			4
#define ARBEITER_AUSFUEHREN			5
#define ARBEITER_DEBUGGER           6
#define ARBEITER_LOESCHEN           7

#include <QString>

/***************************************************************/
/* allgemeine Implementierung, gueltig fuer alle Architekturen */
/***************************************************************/
class CArbeiterSchnittstelle
{
public:
	CArbeiterSchnittstelle();
	virtual ~CArbeiterSchnittstelle();

	int start(int aktion, QString projektVerzeichnis, QString modulName);
	int stop(void);
	int istAktiv(void);
	int leseAusgabe(char *buffer, unsigned int max);
	int schreibeEingabe(const char *buffer);

private:
	virtual int archStart(QString verzeichnis, QString befehl)=0;
	virtual int archStop(void)=0;
	virtual int archIstAktiv(void)=0;
	virtual int archLeseAusgabe(char *buffer, unsigned int max)=0;
	virtual int archSchreibeEingabe(const char *buffer)=0;
};

/*************************************/
/* Linux-spezifische Implementierung */
/*************************************/
#if defined(LINUX)

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <pty.h>

class CArbeiter : public CArbeiterSchnittstelle
{
public:
	CArbeiter();
	~CArbeiter();

private:
	int archStart(QString verzeichnis, QString befehl);
	int archStop(void);
	int archIstAktiv(void);
	int archLeseAusgabe(char *buffer, unsigned int max);
	int archSchreibeEingabe(const char *buffer);

private:
	char *verzeichnis_str;
	char *befehl_str;

	int pty_fd;
	int tty_fd;
	int child_pid;
};

/***************************************/
/* Windows-spezifische Implementierung */
/***************************************/
#elif defined(WIN32)

#include <windows.h>
#include <stdio.h>

class CArbeiter : public CArbeiterSchnittstelle
{
public:
	CArbeiter();
	~CArbeiter();

private:
	int archStart(QString verzeichnis, QString befehl);
	int archStop(void);
	int archIstAktiv(void);
	int archLeseAusgabe(char *buffer, unsigned int max);
	int archSchreibeEingabe(const char *buffer);

	void schreibeFifo(const char *data, unsigned int length);

	static DWORD WINAPI hauptThreadFunc(LPVOID lpParam);
	static DWORD WINAPI warteThreadFunc(LPVOID lpParam);

private:
	char *verzeichnis_str;
	char *befehl_str;

	CRITICAL_SECTION			fifo_section;
	static const unsigned int	fifo_size = 0x10000; // 64kb
	unsigned int				fifo_fill;
	unsigned char				fifo_data[fifo_size];

	HANDLE	haupt_thread_handle;
	HANDLE	warte_thread_handle;

	HANDLE pipe_stdin_read;
	HANDLE pipe_stdin_write;
	HANDLE pipe_stdout_read;
	HANDLE pipe_stdout_write;

	PROCESS_INFORMATION process_information;
};

#endif

#endif
