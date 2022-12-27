#/bin/bash
 cd /home/pavel/Документы/libakrypt-0.x/sphinx 
mkdir -p /home/pavel/Документы/libakrypt-0.x/doc
make html
tar -cjvf /home/pavel/Документы/libakrypt-0.x/doc/libakrypt-doc-0.9.10.tar.bz2 html/* 
make man
cp /home/pavel/Документы/libakrypt-0.x/sphinx/man/aktool.1 /home/pavel/Документы/libakrypt-0.x/aktool 
cp /home/pavel/Документы/libakrypt-0.x/sphinx/man/aktool.1 /home/pavel/Документы/libakrypt-0.x/doc/aktool.1 
gzip --force /home/pavel/Документы/libakrypt-0.x/doc/aktool.1 
make qthelp
qcollectiongenerator qthelp/libakrypt.qhcp
cp /home/pavel/Документы/libakrypt-0.x/sphinx/qthelp/libakrypt.qch /home/pavel/Документы/libakrypt-0.x/doc/libakrypt-doc-0.9.10.qch
make latexpdf
cp /home/pavel/Документы/libakrypt-0.x/sphinx/latex/libakrypt.pdf /home/pavel/Документы/libakrypt-0.x/doc/libakrypt-doc-0.9.10.pdf
cd /home/pavel/Документы/libakrypt-0.x
