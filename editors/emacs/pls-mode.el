(defconst pls-mode-syntax-table
  (let ((syntax-table (make-syntax-table)))
    (modify-syntax-entry ?\/ ". 14" syntax-table)
    (modify-syntax-entry ?\* ". 23" syntax-table)
    syntax-table)
  "Syntax table from PL/Stupid")

(defconst pls-keywords
  '("PROCECURE" "PROC" "FUNCTION" "FUNC" "END" "DCL" "DECLARE" "AS"
    "IF" "ELSE" "ELIF"))

(setq pls-font-lock-defaults
      (let* (
	     (keywords-regex (regexp-opt pls-keywords 'words)))
        `(
	  ("\\_<\\(PROC\\|PROCEDURE\\|FUNC\\|FUNCTION\\)[ \t]+\\([[:alpha:]][[:alnum:]_]*\\)"
	   (1 font-lock-keyword-face)
	   (2 font-lock-function-name-face))
          (,keywords-regex . 'font-lock-keyword-face)
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
