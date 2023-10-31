#ifndef AST_H
# define AST_H 1

typedef enum
{
  A_IF,
  A_FUNCTION
} ASTNodeType;

typedef struct ast_node
{
  ASTNodeType type;
  
  struct ast_node *left;
  struct ast_node *mid;
  struct ast_node *right;

  int lineno;
  int colno;
} ASTNode;

#endif /* !AST_H */
