## Technical Documentation of Smart Outlet

This documentation is written using the [LaTeX](https://www.latex-project.org/about/) framework. Read more about it [here](https://www.latex-project.org/) to have a big picture.

---

### Why LaTeX?
As their official webpage states, it is a high-quality typesetting system. It has incredible features and allows flexibility for technical and scientific documentation. As the document is mainly technical, we understand that it fits better to write it using such a system.

Additionally, it can be control-versioned.

### How to compile
We use [Visual Studio Code](https://code.visualstudio.com/) editor, combined with the [Latex-Workshop](https://marketplace.visualstudio.com/items?itemName=James-Yu.latex-workshop) extension and the alreeady-installed `pdflatex` engine, to compile the entire project.

### Overleaf
[Overleaf](https://www.overleaf.com/) is an easy-to-use, online, collaborative LaTeX editor. In case it cannot be compiled on your machine, this remains a suitable alternative to end up with the same results. Though it is a simple task, we do not provide an already-available collaborative documentation. However, anyone willing to proceed are welcome to do so.

### Libraries
Within LaTex world, it is possible to use external libraries (or packages) to extend certain functionalities of its document preparation system. That is, these packages (e.g [minted](https://ctan.org/pkg/minted?lang=en)) facilitate speed and flexibility when it comes to preparing a sophisticated yet outstanding writing of a document.

Some of these additional packages besides the common ones used to prepare this technical project documentation are:
* appendix: to handle appendix sections
* babel: for dictionary and language purposes
* biblatex: to generate references/bibliography
* xcolor: to access a wider range of colors from the basic palette
* eurosystem: to access euro symbols
* hyperref: to personalize the links
* minted: to highlight source code
* etc

The other packages are mostly relevant to manage the geometry of the document.

### Architecture
To allow an easy-to-follow workspace and based on other recommendations, we use the following file/folder architecture:
```bash
.
├── images
│   ├── logo-black.png
│   └── workflow.png
│   └── ...
├── main.pdf
├── main.tex
├── README.md
├── references.bib
├── scripts
│   ├── code-in-c.c
│   ├── code-in-python.py
│   ├── code-in-javascript.js
│   └── ...
└── sections
    ├── abstract.tex
    ├── appendix.tex
    ├── contents.tex
    ├── instrumentation.tex
    ├── intro.tex
    ├── methodology.tex
    └── theory.tex
    └── ...
```
The entry point is the `main.tex` file.

*NOTE*: _We could have prepared a one-page `tex` document and compile all the writing from there. But as we believe that it can be cumbersome to LIFT (locate - Identify - Flat - Try to be DRY (Do Not Repeat)) through this documentation, we proceed by using this consistent, scalable structure._

### Deliverables
The final pdf is available under the foler `/dist`.
