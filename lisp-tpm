(ql:quickload '("dexador"))

; Fetch -> Build -> Success? -> Mark as installed -> Clean
; 

(defun fetch-git (pkg)
  (dex:get
   (concatenate 'string "https://raw.githubusercontent.com/tarot-linux/tarot-pkgs/main/" pkg)))

(defun fetchurl (url)
  (dex:get url))

(defun build-pkg (pkg)
  (with-open-file (stream "~/Desktop/tpml/test.sh"
			  :direction :output)
    (format stream (fetch-git (concatenate 'string pkg "/" "build"))
     (uiop:run-program "~/Desktop/tpml/test.sh"))))



(defstruct pkg name build deps info version license homepage)

(defvar installed '())

(defun load-installed (filename)
  (with-open-file (in filename)
    (with-standard-io-syntax
      (setf installed (read in)))))

(defun save-installed (filename)
  (with-open-file (out filename
                   :direction :output
                   :if-exists :supersede)
    (with-standard-io-syntax
      (print installed out))))
