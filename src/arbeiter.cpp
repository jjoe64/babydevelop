/* ------------------- */
/* arbeiter.cpp        */
/* (c) by marcel block */
/* ------------------- */

#include "arbeiter.h"

/***************************************************************/
/* allgemeine Implementierung, gueltig fuer alle Architekturen */
/***************************************************************/
CArbeiterSchnittstelle::CArbeiterSchnittstelle()
{
}

CArbeiterSchnittstelle::~CArbeiterSchnittstelle()
{
}

int CArbeiterSchnittstelle::start(int aktion, QString projektVerzeichnis, QString modulName)
{
	switch(aktion)
	{
		case ARBEITER_MOC:
		{
         //QString mocbefehl = "make " + modulName.mid(0, modulName.lastIndexOf('.')) + ".moc.o " + modulName;
         //QString mocbefehl = "make " + modulName.mid(0, modulName.lastIndexOf('.')) + modulName;
         QString mocbefehl = "make " + modulName;
qWarning("ARBEITER_MOC:mocbefehl = %s", mocbefehl.toLatin1().data());
			return this->archStart(projektVerzeichnis, mocbefehl);
		}

		case ARBEITER_KOMPILIEREN:
		{
qWarning("ARBEITER_KOMPILIEREN:makebefehl = %s", QString("make %1").arg(modulName).toLatin1().data());
			return this->archStart(projektVerzeichnis, QString("make %1").arg(modulName));
		}

		case ARBEITER_ALLE_KOMPILIEREN:
		{
qWarning("ARBEITER_ALLE:make compile_all");
			return this->archStart(projektVerzeichnis, "make compile_all");
		}

		case ARBEITER_LINKEN:
		{
qWarning("ARBEITER_LINKEN:make link");
			return this->archStart(projektVerzeichnis, "make link");
		}

		case ARBEITER_RUNDSCHLAG:
		{
qWarning("ARBEITER_RUNDSCHLAG:make all");
			return this->archStart(projektVerzeichnis, "make all");
		}

		case ARBEITER_AUSFUEHREN:
		{
qWarning("ARBEITER_AUSFUEHREN:make run");
			return this->archStart(projektVerzeichnis, "make run");
		}

		case ARBEITER_DEBUGGER:
		{
qWarning("ARBEITER_DEBUGGER:gdb");
		    return this->archStart(projektVerzeichnis, QString("gdb %1").arg(modulName));
		}

		case ARBEITER_LOESCHEN:
		{
qWarning("ARBEITER_LOESCHEN:make clean");
		    return this->archStart(projektVerzeichnis, "make clean");
		}

		default:
		{
			qWarning("Arbeiter: unbekannte Aktion %d!", aktion);
			return -1;
		}
	}

	return -1;
}

int CArbeiterSchnittstelle::stop(void)
{
	return this->archStop();
}

int CArbeiterSchnittstelle::istAktiv(void)
{
	return this->archIstAktiv();
}

int CArbeiterSchnittstelle::leseAusgabe(char *buffer, unsigned int max)
{
	return this->archLeseAusgabe(buffer, max);
}

int CArbeiterSchnittstelle::schreibeEingabe(const char *buffer)
{
    return this->archSchreibeEingabe(buffer);
}

/*************************************/
/* Linux-spezifische Implementierung */
/*************************************/
#if defined(LINUX)

void ReapChild(int pid)
{
   int status;
   wait(&status);
}

CArbeiter::CArbeiter()
{
	this->verzeichnis_str 	= NULL;
	this->befehl_str 		= NULL;
	this->pty_fd 			= -1;
	this->tty_fd 			= -1;
	this->child_pid			= -1;
}

CArbeiter::~CArbeiter()
{
	if(this->verzeichnis_str != NULL) {
		free(this->verzeichnis_str);
		this->verzeichnis_str = NULL;
	}
	if(this->befehl_str != NULL) {
		free(this->befehl_str);
		this->befehl_str = NULL;
	}
}

int CArbeiter::archStart(QString verzeichnis, QString befehl)
{
	// Aufraeumen falls der Prozess noch laeuft
	this->archStop();

	// Verzeichnis/Befehl kopieren
	if(verzeichnis.length() < 1) {
		qWarning("CArbeiter::archStart() ungueltiges Verzeichnis!");
		return -1;
	}

	if(befehl.length() < 1) {
		qWarning("CArbeiter::archStart() ungueltiger Befehl!");
		return -1;
	}

	const char *t = verzeichnis.toAscii().constData();
	this->verzeichnis_str = (char*)malloc(strlen(t)+1);
	if(this->verzeichnis_str == NULL) { qWarning("CArbeiter::archStart() malloc() fehlgeschlagen!"); return -1; }
	memcpy(this->verzeichnis_str, t, strlen(t)+1);

	t = befehl.toAscii().constData();
	this->befehl_str = (char*)malloc(strlen(t)+1);
	if(this->befehl_str == NULL) { qWarning("CArbeiter::archStart() malloc() fehlgeschlagen!"); return -1; }
	memcpy(this->befehl_str, t, strlen(t)+1);

	// keine Zombie-Prozesse
	signal(SIGCHLD, ReapChild);

	// pty+tty device fd anfordern
	if(openpty(&this->pty_fd, &this->tty_fd, NULL, NULL, NULL) < 0) {
		qWarning("CArbeiter::archStart() openpty() fehlgeschlagen!");
		return -1;
	}

	// pty-device soll beim lesen nicht blockieren
	int flags = fcntl(this->pty_fd, F_GETFL, 0);
	if(fcntl(this->pty_fd, F_SETFL, flags | O_NONBLOCK)) {
		qWarning("CArbeiter::archStart() fcntl() fehlgeschlagen!");
		return -2;
	}

	// neuen prozess erzeugen
	this->child_pid = fork();

	// kind-prozess?
	if(this->child_pid == 0)
	{
		// stdin, stdout, stderr auf das tty-device umbiegen
		dup2(this->tty_fd, STDIN_FILENO);
		dup2(this->tty_fd, STDOUT_FILENO);
		dup2(this->tty_fd, STDERR_FILENO);

		// arbeitsverzeichnis wechseln
		if(chdir(verzeichnis_str)) {
			qWarning("Fehler: kann nicht ins Arbeitsverzeichnis '%s' wechseln!", verzeichnis_str);
		}

		// befehl ausfuehren
		int ret = system(befehl_str);
		qWarning(">>> fertig (Code %d) <<<", ret);

		// selbstmord
		kill(getpid(),9);
		exit(-1);
		for(;;);
	}

	return 0;
}

int CArbeiter::archStop(void)
{
	// Speicher freigeben
	if(this->verzeichnis_str != NULL) {
		free(this->verzeichnis_str);
		this->verzeichnis_str = NULL;
	}
	if(this->befehl_str != NULL) {
		free(this->befehl_str);
		this->befehl_str = NULL;
	}

	// Laueft Prozess noch?
	if(this->archIstAktiv()) {

		// Prozess killen
		kill(this->child_pid, 9);
		this->child_pid = -1;

		// pty/tty-Devices schliessen
		close(this->pty_fd);
		close(this->tty_fd);
		this->pty_fd = -1;
		this->tty_fd = -1;
	}

	return 0;
}

int CArbeiter::archIstAktiv(void)
{
	if(this->child_pid == -1) {
		return 0;
	}

	// teste ob der Prozess noch laeuft
	// Null-Signal dient zum validieren von Prozess-ID's
	int ret = kill(this->child_pid, 0);
	if(ret == 0) {
		// prozess laeuft noch
		return 1;
	}

	return 0;
}

int CArbeiter::archLeseAusgabe(char *buffer, unsigned int max)
{
	return read(this->pty_fd, buffer, max);
}

int CArbeiter::archSchreibeEingabe(const char *buffer)
{
    return write(this->pty_fd, buffer, strlen(buffer));
}

/***************************************/
/* Windows-spezifische Implementierung */
/***************************************/
#elif defined(WIN32)

CArbeiter::CArbeiter()
{
	this->verzeichnis_str = NULL;
	this->befehl_str = NULL;

	// FIFO initialisieren
	InitializeCriticalSection(&this->fifo_section);
	this->fifo_fill = 0;
	memset(this->fifo_data, 0, this->fifo_size);

	this->haupt_thread_handle = NULL;
	this->warte_thread_handle = NULL;

	this->pipe_stdin_read = NULL;
	this->pipe_stdin_write = NULL;
	this->pipe_stdout_read = NULL;
	this->pipe_stdout_write = NULL;

	this->process_information.hProcess = NULL;
	this->process_information.hThread = NULL;
	this->process_information.dwProcessId = 0;
	this->process_information.dwThreadId = 0;
}

CArbeiter::~CArbeiter()
{
	DeleteCriticalSection(&this->fifo_section);

	if(this->verzeichnis_str) {
		free(this->verzeichnis_str);
		this->verzeichnis_str = NULL;
	}
	if(this->befehl_str) {
		free(this->befehl_str);
		this->befehl_str = NULL;
	}
}

int CArbeiter::archStart(QString verzeichnis, QString befehl)
{
	// Aufraeumen & Thread/Prozess killen falls sie noch laufen
	this->archStop();

	// Verzeichnis/Befehl kopieren
	if(verzeichnis.length() < 1) {
		qWarning("CArbeiter::archStart() ungueltiges Verzeichnis!");
		return -1;
	}

	if(befehl.length() < 1) {
		qWarning("CArbeiter::archStart() ungueltiger Befehl!");
		return -1;
	}

	const char *t = verzeichnis.toAscii().constData();
	this->verzeichnis_str = (char*)malloc(strlen(t)+1);
	if(this->verzeichnis_str == NULL) { qWarning("CArbeiter::archStart() malloc() fehlgeschlagen!"); return -1; }
	memcpy(this->verzeichnis_str, t, strlen(t)+1);

	t = befehl.toAscii().constData();
	this->befehl_str = (char*)malloc(strlen(t)+1);
	if(this->befehl_str == NULL) { qWarning("CArbeiter::archStart() malloc() fehlgeschlagen!"); return -1; }
	memcpy(this->befehl_str, t, strlen(t)+1);

	// neuen Thread erzeugen
	this->haupt_thread_handle = CreateThread(	NULL,					// security attributes
												0,						// stack size
												this->hauptThreadFunc,	// start address
												(void*)this,        	// thread parameter (pointer to CArbeiter*)
												0,						// creation flags
												NULL);					// thread id
	if(this->haupt_thread_handle == NULL) {
		qWarning("CArbeiter::archStart() CreateThread() fehlgeschlagen!");
		return -1;
	}

	// fertig, Thread erledigt den Rest
	return 0;
}

int CArbeiter::archStop(void)
{
	// Speicher freigeben
	if(this->verzeichnis_str != NULL) {
		free(this->verzeichnis_str);
		this->verzeichnis_str = NULL;
	}
	if(this->befehl_str != NULL) {
		free(this->befehl_str);
		this->befehl_str = NULL;
	}

	// Laeufen die Threads noch?
	if(WaitForSingleObject(this->haupt_thread_handle, 0) == WAIT_TIMEOUT) {
		// Thread killen
		if(TerminateThread(this->haupt_thread_handle, 0) == FALSE) {
			qWarning("CArbeiter::archStop() TerminateThread() fehlgeschlagen!");
		}
		this->haupt_thread_handle = NULL;
	}
	if(WaitForSingleObject(this->warte_thread_handle, 0) == WAIT_TIMEOUT) {
		// Thread killen
		if(TerminateThread(this->warte_thread_handle, 0) == FALSE) {
			qWarning("CArbeiter::archStop() TerminateThread() fehlgeschlagen!");
		}
		this->warte_thread_handle = NULL;
	}

	// Laeuft der Prozess noch?
	if(WaitForSingleObject(this->process_information.hProcess, 0) == WAIT_TIMEOUT) {
		// Prozess killen
		if(TerminateProcess(this->process_information.hProcess, 0) == FALSE) {
			qWarning("CArbeiter::archStop() TerminateProcess() fehlgeschlagen!");
		}
		this->process_information.hProcess		= NULL;
		this->process_information.hThread		= NULL;
		this->process_information.dwProcessId	= 0;
		this->process_information.dwThreadId	= 0;
	}

	// Pipes freigeben
	CloseHandle(this->pipe_stdin_read);
	CloseHandle(this->pipe_stdin_write);
	CloseHandle(this->pipe_stdout_read);
	CloseHandle(this->pipe_stdout_write);

	return 0;
}

int CArbeiter::archIstAktiv(void)
{
	// teste ob der Prozess noch laeuft
	DWORD dwRet = WaitForSingleObject(this->process_information.hProcess, 0);
	if(dwRet == WAIT_TIMEOUT) {
		// Prozess laeuft noch
		return 1;
	}

	return 0;
}

int CArbeiter::archLeseAusgabe(char *buffer, unsigned int max)
{
	EnterCriticalSection(&this->fifo_section);

	int kopiert = 0;
	if(this->fifo_fill > 0) {

		if(this->fifo_fill <= max) {
			// ausreichend Platz im Ausgabe-Buffer
			kopiert = this->fifo_fill;
			memcpy(buffer, this->fifo_data, kopiert);
			this->fifo_fill = 0;
		}
		else {
			// nicht genug Platz im Ausgabe-Buffer
			kopiert = max;
			memcpy(buffer, this->fifo_data, kopiert);
			this->fifo_fill -= kopiert;

			// daten verschieben um die luecke zu schliessen
			char temp_buffer[this->fifo_size];
			memcpy(temp_buffer, this->fifo_data+kopiert, this->fifo_fill);
			memcpy(this->fifo_data, temp_buffer, this->fifo_fill);
		}
	}

	LeaveCriticalSection(&this->fifo_section);

	return kopiert;
}

int CArbeiter::archSchreibeEingabe(const char *buffer)
{
    BOOL success = FALSE;
    DWORD written = 0;

    success = WriteFile(this->pipe_stdin_write, buffer, strlen(buffer), &written, NULL);

    if(success == FALSE) {
        qWarning("CArbeiter::archSchreibeEingabe() WriteFile() fehlgeschlagen!");
        return -1;
    }

    return (int)written;
}

void CArbeiter::schreibeFifo(const char *data, unsigned int length)
{
	EnterCriticalSection(&this->fifo_section);

	unsigned int fifo_space = this->fifo_size - this->fifo_fill;
	if(length <= fifo_space) {
		// ausreichend Platz im FIFO
		memcpy(this->fifo_data+this->fifo_fill, data, length);
		this->fifo_fill += length;
	}
	else {
		// nicht genug Platz im FIFO
		memcpy(this->fifo_data+this->fifo_fill, data, fifo_space);
		this->fifo_fill += fifo_space;

		qWarning("CArbeiter::schreibeFifo() FIFO full!");
	}

	LeaveCriticalSection(&this->fifo_section);
}

DWORD WINAPI CArbeiter::hauptThreadFunc(LPVOID lpParam)
{
	CArbeiter *arbeiter = (CArbeiter*)lpParam;

	// Pipe-Handles vererben
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength				= sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle		= TRUE;
	saAttr.lpSecurityDescriptor	= NULL;

	// STDOUT-Pipe erzeugen
	if(!CreatePipe(&arbeiter->pipe_stdout_read, &arbeiter->pipe_stdout_write, &saAttr, 0)) {
		qWarning("CArbeiter::threadFunc() CreatePipe(STDOUT) fehlgeschlagen!\n");
		return 0;
	}

	// Lese-Handle der STDOUT-Pipe nicht vererben
	if(!SetHandleInformation(arbeiter->pipe_stdout_read, HANDLE_FLAG_INHERIT, 0)) {
		qWarning("CArbeiter::threadFunc() SetHandleInformation(STDOUT) fehlgeschlagen!\n");
		return 0;
	}

	// STDIN-Pipe erzeugen
	if(!CreatePipe(&arbeiter->pipe_stdin_read, &arbeiter->pipe_stdin_write, &saAttr, 0)) {
		qWarning("CArbeiter::threadFunc() CreatePipe(STDIN) fehlgeschlagen!\n");
		return 0;
	}

	// Schreib-Handle der STDIN-Pipe nicht vererben
	if(!SetHandleInformation(arbeiter->pipe_stdin_write, HANDLE_FLAG_INHERIT, 0)) {
		qWarning("CArbeiter::threadFunc() SetHandleInformation(STDIN) fehlgeschlagen!\n");
		return 0;
	}

	// STARTUPINFO fuer den neuen Prozess vorbereiten
	STARTUPINFO startupInfo;
	BOOL success = FALSE;

 	ZeroMemory(&arbeiter->process_information, sizeof(PROCESS_INFORMATION));
	ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
	startupInfo.cb			= sizeof(STARTUPINFO);
	startupInfo.hStdError	= arbeiter->pipe_stdout_write;
	startupInfo.hStdOutput	= arbeiter->pipe_stdout_write;
	startupInfo.hStdInput	= arbeiter->pipe_stdin_read;
	startupInfo.dwFlags		|= STARTF_USESTDHANDLES;

	// Prozess erzeugen
	success = CreateProcess(	NULL,								// application name
								arbeiter->befehl_str,				// command line
								NULL,								// process security attributes
								NULL,								// primary thread security attributes
								TRUE,								// handles are inherited
								0,									// creation flags
								NULL,								// use parent's environment
								arbeiter->verzeichnis_str,			// current directory
								&startupInfo,						// startup information
								&arbeiter->process_information);	// process information
	if(success == FALSE) {
		DWORD lastError = GetLastError();
		LPTSTR wBuffer;
		char buffer[128];

		// ausgeben was nicht geklappt hat
		sprintf(buffer, "Fehler: Der Befehl '%s' im Verzeichnis '%s' konnte nicht ausgefuehrt werden!\n", arbeiter->befehl_str, arbeiter->verzeichnis_str);
		arbeiter->schreibeFifo(buffer, strlen(buffer));

		// versuche Fehlercode lesbar zu machen
		if(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, lastError, 0, (LPTSTR)&wBuffer, 0, NULL) == 0) {
			// keine Fehlerbeschreibung vorhanden, stattdessen Fehlercode ausgeben
			sprintf(buffer, "Beschreibung: unbekannter Fehler, Code=%u", (unsigned int)lastError);
			arbeiter->schreibeFifo(buffer, strlen(buffer));
		} else {
			// TCHAR-Array zu QString konvertieren
			QString errorString;
			#ifdef UNICODE
			errorString = QString::fromUtf16((ushort*)wBuffer);
			#else
			errorString = QString::fromLocal8Bit(wBuffer);
			#endif

			// Fehlerbeschreibung in Ausgabe-FIFO schreiben
			errorString.remove('\n');
			errorString.remove('\r');
			sprintf(buffer, "Beschreibung: '%s'", errorString.toAscii().constData());
			arbeiter->schreibeFifo(buffer, strlen(buffer));

			// TCHAR-Array freigeben
			LocalFree(wBuffer);
		}

		return 0;
	}

	// Warte-Thread erzeugen
	arbeiter->warte_thread_handle = CreateThread(	NULL,						// security attributes
													0,							// stack size
													arbeiter->warteThreadFunc,	// start address
													(void*)arbeiter,       		// thread parameter (pointer to CArbeiter*)
													0,							// creation flags
													NULL);						// thread id
	if(arbeiter->warte_thread_handle == NULL) {
		qWarning("CArbeiter::hauptThreadFunc() CreateThread() fehlgeschlagen!");
	}

	// Endlosschleife die die Stdout-Daten vom Arbeits-Prozess in den FIFO scheffelt
	for(;;) {
		DWORD read=0;
		char buffer[1024];
		BOOL success = FALSE;

		success = ReadFile(arbeiter->pipe_stdout_read, buffer, 1024, &read, NULL);

		if(success && read > 0) {
			arbeiter->schreibeFifo(buffer, read);
		}
	}

	return 0;
}

DWORD WINAPI CArbeiter::warteThreadFunc(LPVOID lpParam)
{
	CArbeiter *arbeiter = (CArbeiter*)lpParam;
	DWORD exitCode = 0;
	char buffer[128] = "";

	// Warten bis der Arbeits-Prozess terminiert
	WaitForSingleObject(arbeiter->process_information.hProcess, INFINITE);

	// Rueckgabe-Code des terminierten Prozess erfragen
	if(!GetExitCodeProcess(arbeiter->process_information.hProcess, &exitCode)) {
		qWarning("CArbeiter::warteThreadFunc() GetExitCodeProcess() fehlgeschlagen!");
	}

	// Fertig-Meldung mit Rueckgabe-Code in den Ausgabe-FIFO schreiben
	sprintf(buffer, ">>> fertig (Code %u) <<<\n", (unsigned int)exitCode);
	arbeiter->schreibeFifo(buffer, strlen(buffer));

	// Warte-Thread beenden
	return 0;
}

#endif
