(defconst pls-mode-syntax-table
  (let ((syntax-table (make-syntax-table)))
    (modify-syntax-entry ?\/ ". 14" syntax-table)
    (modify-syntax-entry ?\* ". 23" syntax-table)
    syntax-table)
  "Syntax table from PL/Stupid")

(defconst pls-keywords
  '("PROCECURE" "PROC" "FUNCTION" "FUNC" "END" "DCL" "DECLARE" "AS"
	"IF" "ELSE" "ELIF" "THEN" "BEGIN", "WHILE", "FOR", "GOTO" "EXTERN"
	"CLASS" "CONST" "INIT"))

(defconst pls-types
  '("INT8" "INT16" "INT32" "UINT8" "UINT16" "UINT32"))

(defconst pls-constants
  '("TRUE" "FALSE" "NIL"))

(defconst pls-builtins
  '("exit"))

(setq pls-font-lock-defaults
      (let* (
			 (keywords-regex (regexp-opt pls-keywords 'words))
			 (types-regex (regexp-opt pls-types 'words))
			 (constant-regex (regexp-opt pls-constants 'words))
			 (builtin-regex (regexp-opt pls-builtins 'words)))
        `(
		  ("\\_<\\(PROC\\|PROCEDURE\\|FUNC\\|FUNCTION\\)[ \t]+\\([[:alpha:]][[:alnum:]_]*\\)"
		   (1 font-lock-keyword-face)
		   (2 font-lock-function-name-face))
		  ("\\_<\\(DECLARE\\|DCL\\)[ \t]+\\([[:alpha:]_][[:alnum:]_]*\\)[ \t]+\\(AS\\)[ \t]+\\([[:alpha:]_][[:alnum:]_]*\\)"
		   (1 font-lock-keyword-face)
		   (2 font-lock-variable-name-face)
		   (3 font-lock-keyword-face)
		   (4 font-lock-type-face))
          (,keywords-regex . 'font-lock-keyword-face)
		  (,types-regex . 'font-lock-type-face)
		  (,constant-regex . 'font-lock-constant-face)
		  (,builtin-regex . 'font-lock-builtin-face)
          )))

;;;###autoload
(define-derived-mode pls-mode prog-mode "PL/Stupid"
  "Major mode for PL/Stupid code."
  :group 'pls-mode
  :syntax-table pls-mode-syntax-table
  (setq font-lock-defaults '((pls-font-lock-defaults)))
  (set-syntax-table pls-mode-syntax-table)
  (setq-local comment-start "/*")
  (setq-local comment-end "*/"))

(provide 'pls-mode)
