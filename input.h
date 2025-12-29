#ifndef INPUT_H
#define INPUT_H

#define MAX_LEN 16

void Input_Init(void);
void Input_HandleKey(char key);
const char *Input_GetExpr(void);
void Input_SetExpr(const char *s);

/* Error ???? */
int  Input_HasError(void);
void Input_ClearError(void);

#endif
