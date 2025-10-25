# CP-Notebook
Competitive Programming Notebook from Adrián Muro Garduño.
Tested and working algorithms and techniques.
Will be updating new content.

## Generating team notebook
The included Python scripts can generate the notebook in PDF or HTML format. Both scripts read the contents of the notebook from contents.txt.

### PDF version
Requires: [Python 2/3](https://www.python.org/), [latexmk](https://www.ctan.org/pkg/latexmk/)

Script for generating the PDF file is generate_pdf.py. The LaTeX template that the script uses is notebook.tex. It recognizes common file extensions for C/C++/Java/Python and applies syntax highlighting. In order to change the color scheme or add additional languages, both notebook.tex and generate_pdf.py should be modified accordingly.

Credits to [Stanford ACM repo](https://github.com/jaehyunp/stanfordacm) in which some files were copied from there.