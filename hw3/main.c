#include <stdio.h>
#include <string.h>

#define TOKEN_EOF    0
#define TOKEN_NUM    1
#define TOKEN_PLUS   2
#define TOKEN_LPAREN 3
#define TOKEN_RPAREN 4
#define TOKEN_ERROR  5

// 全域變數
int current_token;
char buffer[256];
int error_flag = 0;
int depth = 0; 

int is_space(char c) { return (c == ' ' || c == '\t' || c == '\n' || c == '\r'); }
int is_alpha(char c) { return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'); }
int is_digit(char c) { return (c >= '0' && c <= '9'); }
int is_alnum(char c) { return (is_alpha(c) || is_digit(c)); }

// 將你 HW2 的主要掃描邏輯封裝成每次前進一個 Token 的 Scanner
void advance() {
    int c;
    while ((c = getchar()) != EOF) {
        if (is_space(c)) continue;

        // 使用你 HW2 的一模一樣的數字偵測與 ungetc 模式
        if (is_digit(c)) {
            int i = 0;
            buffer[i++] = (char)c;
            while (is_digit(c = getchar())) {
                buffer[i++] = (char)c;
            }
            ungetc(c, stdin);
            buffer[i] = '\0';
            current_token = TOKEN_NUM;
            return;
        }

        // 處理符號項目
        if (c == '+') { current_token = TOKEN_PLUS; return; }
        if (c == '(') { current_token = TOKEN_LPAREN; return; }
        if (c == ')') { current_token = TOKEN_RPAREN; return; }

        // 遇到不合文法的字元
        current_token = TOKEN_ERROR;
        return;
    }
    current_token = TOKEN_EOF;
}

// Parser 函式宣告
void parse_S();
void parse_S_prime();
void parse_E();

// 印出符合階層的空格縮進
void print_indent() {
    for (int i = 0; i < depth; i++) {
        printf("  "); 
    }
}

// S -> E S'
void parse_S() {
    if (error_flag) return;

    if (current_token == TOKEN_NUM || current_token == TOKEN_LPAREN) {
        print_indent();
        printf("S -> E S'\n");
        
        depth++; // 進入 E 的深度
        parse_E();
        
        depth++; // 進入 S' 之前的深度
        parse_S_prime();
        
        depth--; 
        depth--; 
    } else {
        printf("Parse Error\n");
        error_flag = 1;
    }
}

// S' -> + S | epsilon
void parse_S_prime() {
    if (error_flag) return;

    if (current_token == TOKEN_PLUS) {
        print_indent();
        printf("S' -> +S\n");
        advance(); // 消耗 '+'
        
        depth++; // 修正：進入下一層 S 之前往右移，確保 S -> E S' 會順利遞進！
        parse_S(); 
        depth--; // 恢復深度
    } else if (current_token == TOKEN_RPAREN || current_token == TOKEN_EOF) {
        return; // epsilon 默默 return
    } else {
        printf("Parse Error\n");
        error_flag = 1;
    }
}

// E -> num | ( S )
void parse_E() {
    if (error_flag) return;

    if (current_token == TOKEN_NUM) {
        print_indent();
        printf("%s\n", buffer); // 印出數字葉子節點
        advance(); // 消耗數字
    } else if (current_token == TOKEN_LPAREN) {
        print_indent();
        printf("E -> (S)\n");
        advance(); // 消耗 '('
        
        depth++; // 進入括號內部的子樹結構
        parse_S();
        depth--; // 離開括號內部的子樹結構
        
        if (current_token == TOKEN_RPAREN) {
            advance(); // 消耗 ')'
        } else {
            printf("Parse Error\n");
            error_flag = 1;
        }
    } else {
        printf("Parse Error\n");
        error_flag = 1;
    }
}

int main() {
    advance(); // 預先讀取第一個 Token
    parse_S(); // 開始從起點文法 S 進行解析

    // 如果解析完畢後，Token 沒有到達結尾 (EOF)，代表後面有多餘的錯誤字元
    if (!error_flag && current_token != TOKEN_EOF) {
        printf("Parse Error\n");
    }

    return 0;
}
