#define WEBVIEW_IMPLEMENTATION
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <webview.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

/** 
 * char *runProcess(char *cmd)
 * 
 * run a process command and return the output
 * 
 * @param cmd c string of the command to run.
 * @return	Returns a malloc'd string cotaining the 
 * 			results of the commands output on success,
 * 			NULL on command error. 
 **/
char *runProcess(char *cmd) {
	char *ret = NULL;
    FILE *fp = NULL, *out = NULL;
	size_t size = 0;
	char buffer[1024];
    
    fp = popen(cmd, "r");

    if (fp != NULL) {
		out = open_memstream(&ret, &size);
		if (out == NULL) handle_error("Could not open memory for streaming!");
				
		for(char *res = ""; res != NULL; res = fgets(buffer, sizeof(buffer), fp)) {
			if (fprintf(out,"%s",buffer) < 0) handle_error("Error while reading command output!");			
		}        
		fprintf(out,"%c",'\000');
    }
	
	pclose(fp);
	fclose(out);

    return ret;
}

/** 
 * void theLoungeInit(void)
 * 
 * launch thelounge node.js process if it is not already running.
 **/
void theLoungeInit(void) {
	char *output = NULL;

	output = runProcess("ps afx | grep lounge | grep -v 'grep'");

	if (output == NULL || strlen(output) == 0) {
		char command[50];
		strcpy(command, "thelounge start &");
		system(command);
	}

	if (output) free(output);
	return;
}

/**
 * void webviewInit(void)
 * 
 * launch the webview instance
 **/
void webviewInit(void) {	
	/* Open localhost running of instance thelounge on default port */
	webview("Parlor","http://localhost:9000", 1024, 768, 1);
}

int main() {
	
	pid_t pid, wpid;
	int wstatus;

	pid = fork();
	if (pid == 0) {
		theLoungeInit();
		_exit(0);
	} else {
		do {
			waitpid(pid, &wstatus, WUNTRACED | WCONTINUED);
		} while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
		webviewInit();
	}

 	exit(EXIT_SUCCESS);
}