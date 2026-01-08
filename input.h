#ifndef INPUT_H
#define INPUT_H

/* Maximum length of expression */
#define MAX_LEN 16

/* Initialize input handling module */
void Input_Init(void);

/* Process a key input */
void Input_HandleKey(char key);

/* Get current expression string */
const char *Input_GetExpr(void);

/* Set expression string */
void Input_SetExpr(const char *s);

/* Query error state */
int  Input_HasError(void);

/* Clear error state */
void Input_ClearError(void);

/* Query shift mode state */
int  Input_IsShift(void);

#endif
