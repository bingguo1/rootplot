#!/bin/bash

for f in *.png
do
    fcaption=${f/_/-}
    fcaption=${fcaption/_/-}
    fcaption=${fcaption/_/-}
    # cause detokenize with underscore doesnot work in .lof(lisf of figures) proecssing
    
   echo " \begin{figure}[htb]"
   echo "     \includegraphics[width=0.9\textwidth]{\detokenize{${f}}}"
   echo "          \caption{\detokenize{${fcaption}}}"
   echo " \end{figure}"
   echo " \newpage"
   echo
done

echo "\end{document}"
