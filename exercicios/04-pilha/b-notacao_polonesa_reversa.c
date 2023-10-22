#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 105

// Função para verificar se um caractere é um operador
int isOperator(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Função para determinar a precedência de um operador
int precedence(char c) {
  if (c == '+' || c == '-')
    return 1;
  if (c == '*' || c == '/')
    return 2;
  return 0;
}

// Função para converter a notação infixa para pós-fixa
void infixToPostfix(char *infix, char *postfix) {
  char stack[MAX_CHAR];
  int top = -1;
  int i, j = 0;

  for (i = 0; infix[i]; i++) {
    if (infix[i] == ' ') {
      continue;
    } else if (infix[i] >= '0' && infix[i] <= '9') {
      while (infix[i] >= '0' && infix[i] <= '9') {
        postfix[j++] = infix[i++];
      }
      postfix[j++] = ' ';
      i--;
    } else if (isOperator(infix[i])) {
      while (top >= 0 && precedence(stack[top]) >= precedence(infix[i])) {
        postfix[j++] = stack[top--];
        postfix[j++] = ' ';
      }
      stack[++top] = infix[i];
    } else if (infix[i] == '(') {
      stack[++top] = infix[i];
    } else if (infix[i] == ')') {
      while (top >= 0 && stack[top] != '(') {
        postfix[j++] = stack[top--];
        postfix[j++] = ' ';
      }
      top--; // Remove '(' from the stack
    }
  }

  while (top >= 0) {
    postfix[j++] = stack[top--];
    postfix[j++] = ' ';
  }
  postfix[j] = '\0';
}

int main() {
  char infix[MAX_CHAR];
  char postfix[MAX_CHAR];

  // Leitura da expressão infixa
  fgets(infix, MAX_CHAR, stdin);
  infix[strcspn(infix, "\n")] = '\0'; // Remove a quebra de linha

  infixToPostfix(infix, postfix);
  printf("%s\n", postfix);

  return 0;
}
