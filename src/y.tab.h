#define TOK_VOID 257
#define TOK_INT 258
#define TOK_INTVAL 259
#define TOK_BOOL 260
#define TOK_TRUE 261
#define TOK_FALSE 262
#define TOK_IDENT 263
#define TOK_IF 264
#define TOK_ELSE 265
#define TOK_WHILE 266
#define TOK_FOR 267
#define TOK_PRINT 268
#define TOK_SEMICOL 269
#define TOK_COMMA 270
#define TOK_LPAR 271
#define TOK_RPAR 272
#define TOK_LACC 273
#define TOK_RACC 274
#define TOK_STRING 275
#define TOK_DO 276
#define TOK_GT 277
#define TOK_LT 278
#define TOK_THEN 279
#define TOK_AFFECT 280
#define TOK_OR 281
#define TOK_AND 282
#define TOK_BOR 283
#define TOK_BXOR 284
#define TOK_BAND 285
#define TOK_EQ 286
#define TOK_NE 287
#define TOK_GE 288
#define TOK_LE 289
#define TOK_SRL 290
#define TOK_SRA 291
#define TOK_SLL 292
#define TOK_PLUS 293
#define TOK_MINUS 294
#define TOK_MUL 295
#define TOK_DIV 296
#define TOK_MOD 297
#define TOK_UMINUS 298
#define TOK_NOT 299
#define TOK_BNOT 300
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
    int32_t intval;
    char * strval;
    node_t ptr;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
